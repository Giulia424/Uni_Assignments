#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
// make && make -f Makefile.example && LD_LIBRARY_PATH=. ./so_exec so_test_prog

#include "exec_parser.h"

static so_exec_t *exec;
static int fd;
size_t nbytes;

static struct sigaction sd; // default

// function to generate segfault when necessary
void gen_segv()
{
	signal(SIGSEGV, SIG_DFL);
	raise(SIGSEGV);
}

static void segv_handler(int signum, siginfo_t *info, void *context)
{
	unsigned int segfault_addr = (unsigned int)info->si_addr;
	int size_page = getpagesize();
	int nr_pages_mem = 0;
	int nr_pages_file = 0;
	int entryp_page = 0;
	int endp_page = 0;
	int seg_fault_page;
	int nr_segm = 0;
	int entryp_segm_mem = 0;
	int endp_segm_mem = 0;
	int seg_fault;
	int mem_size_seg_fault;
	int file_size_seg_fault;
	nr_segm = exec->segments_no;
	seg_fault = -1;

	// First we try to find in which segment the segfault is
	for (int i = 0; i < nr_segm; i++)
	{
		entryp_segm_mem = exec->segments[i].vaddr;
		endp_segm_mem = exec->segments[i].vaddr + exec->segments[i].mem_size;
		mem_size_seg_fault = exec->segments[i].mem_size;
		file_size_seg_fault = exec->segments[i].file_size;
		nr_pages_mem = mem_size_seg_fault / size_page + 1;
		nr_pages_file = file_size_seg_fault / size_page + 1;
		if ((segfault_addr >= entryp_segm_mem) && (segfault_addr <= endp_segm_mem))
		{
			seg_fault = i;
			break;
		}
	}
	if (seg_fault == -1)
		gen_segv();

	//  Now we must find in which page the segfault is
	entryp_page = exec->segments[seg_fault].vaddr;
	endp_page = exec->segments[seg_fault].vaddr + size_page;
	if (seg_fault >= 0)
	{
		puts("as");
		for (int j = 0; j < nr_pages_mem; j++)
			if ((int)info->si_addr < endp_page)
			{
				seg_fault_page = j;
				break;
			}
			else
			{
				entryp_page += size_page;
				endp_page += size_page;
			}
	}
	// From now on, we are going to try to see if the page we found the segfault to be on is
	// mapped or not. We are going to use de void pointer named data, from the so_seg structure
	if (exec->segments[seg_fault].data == NULL)
		exec->segments[seg_fault].data = calloc(nr_pages_mem, sizeof(char));
	char *mapped = exec->segments[seg_fault].data;
	// We created a vector to check whether or not the pages of a segment have been already visited
	// or not; we made sure the "mapped" vector is initialised with 0, using the calloc function
	// Before we use the mmap function we have to make sure we have all the parameters
	// so let's find the permission , the executable etc.
	// For the permission within said segment, we will be using the variable perm
	// from the so_seg structure
	unsigned int perm = exec->segments[seg_fault].perm;
	// For the executable, we will be using the global variable fd and the open function
	// Fot the offset, we will be using the variable offset,from the so_seg structure
	int offset = exec->segments[seg_fault].offset;
	// We are going to be mapping only the unmapped pages, as i said before
	char *addr;
	int *entrypage = (int *)entryp_page;

	if (seg_fault >= 0)
	{
		if (mapped[seg_fault_page] == 0)
		{
			addr = mmap(entrypage, size_page, PROT_WRITE, MAP_FIXED | MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
			// We must check if the mapping worked
			if (addr == MAP_FAILED)
				exit(1);
			else
				mapped[seg_fault_page] = 1;
			// On success, the mmap() returns 0; for failure, the function returns MAP_FAILED.
		}
		else if (mapped[seg_fault_page] == 1)
			gen_segv();
	}
	// Now we must copy the data  from the page where we found the segfault
	// Here we check if the segfault is in the file_size of the segment, so if we have to copy it
	if (seg_fault_page < nr_pages_file - 1)
	{
		nbytes = size_page;
		offset = offset + (size_page * seg_fault_page);
		lseek(fd, offset, SEEK_SET);
		read(fd, addr, nbytes);
	}
	else if (seg_fault_page == nr_pages_file - 1)
	{
		nbytes = file_size_seg_fault - seg_fault_page * size_page;
		offset = offset + (size_page * seg_fault_page);
		lseek(fd, offset, SEEK_SET);
		read(fd, addr, nbytes);
	}
	if (mprotect(addr, getpagesize(), perm) == -1)
	{
		perror("sigaction");
		return -1;
	}
}

int so_init_loader(void)
{
	int rc;
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = segv_handler;
	sa.sa_flags = SA_SIGINFO;
	rc = sigaction(SIGSEGV, &sa, &sd);
	if (rc < 0)
	{
		perror("sigaction");
		return -1;
	}
	return 0;
}

int so_execute(char *path, char *argv[])
{
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("c1");
		exit(1);
	}
	exec = so_parse_exec(path);
	if (!exec)
		return -1;

	so_start_exec(exec, argv);
	if (close(fd) < 0)
	{
		perror("close");
		exit(1);
	}
	return -1;
}