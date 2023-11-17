// Author: APD team, except where source was noted

#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define CONTOUR_CONFIG_COUNT 16
#define FILENAME_MAX_SIZE 50
#define STEP 8
#define SIGMA 200
#define RESCALE_X 2048
#define RESCALE_Y 2048

#define CLAMP(v, min, max) \
    if (v < min)           \
    {                      \
        v = min;           \
    }                      \
    else if (v > max)      \
    {                      \
        v = max;           \
    }
#define min(a, b) (((a) < (b)) ? (a) : (b))

struct bic_int
{
    ppm_image *new_image;
    ppm_image *image;
    uint8_t sample[3];
    int P;
    long id;
};
// Creates a map between the binary configuration (e.g. 0110_2) and the corresponding pixels
// that need to be set on the output image. An array is used for this map since the keys are
// binary numbers in 0-15. Contour images are located in the './contours' directory.
ppm_image **init_contour_map()
{
    ppm_image **map = (ppm_image **)malloc(CONTOUR_CONFIG_COUNT * sizeof(ppm_image *));
    if (!map)
    {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    for (int i = 0; i < CONTOUR_CONFIG_COUNT; i++)
    {
        char filename[FILENAME_MAX_SIZE];
        sprintf(filename, "./contours/%d.ppm", i);
        map[i] = read_ppm(filename);
    }

    return map;
}

// Updates a particular section of an image with the corresponding contour pixels.
// Used to create the complete contour image.
void update_image(ppm_image *image, ppm_image *contour, int x, int y)
{
    for (int i = 0; i < contour->x; i++)
    {
        for (int j = 0; j < contour->y; j++)
        {
            int contour_pixel_index = contour->x * i + j;
            int image_pixel_index = (x + i) * image->y + y + j;

            image->data[image_pixel_index].red = contour->data[contour_pixel_index].red;
            image->data[image_pixel_index].green = contour->data[contour_pixel_index].green;
            image->data[image_pixel_index].blue = contour->data[contour_pixel_index].blue;
        }
    }
}

// Corresponds to step 1 of the marching squares algorithm, which focuses on sampling the image.
// Builds a p x q grid of points with values which can be either 0 or 1, depending on how the
// pixel values compare to the `sigma` reference value. The points are taken at equal distances
// in the original image, based on the `step_x` and `step_y` arguments.

// Each pixel value  represents a single sample of light and the parameters stepX and stepY control
// the resolution of the sample. Grid will be used to hold the bit matrix
unsigned char **sample_grid(ppm_image *image, int step_x, int step_y, unsigned char sigma)
{
    int p = image->x / step_x; // nr of pixels per line
    int q = image->y / step_y; // nr of pixels per column

    unsigned char **grid = (unsigned char **)malloc((p + 1) * sizeof(unsigned char *));
    if (!grid)
    {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    for (int i = 0; i <= p; i++)
    {
        grid[i] = (unsigned char *)malloc((q + 1) * sizeof(unsigned char));
        if (!grid[i])
        {
            fprintf(stderr, "Unable to allocate memory\n");
            exit(1);
        }
    }

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < q; j++)
        {
            ppm_pixel curr_pixel = image->data[i * step_x * image->y + j * step_y];
            // step_x is equal to the length of an entire pixel
            unsigned char curr_color = (curr_pixel.red + curr_pixel.green + curr_pixel.blue) / 3;

            if (curr_color > sigma)
            {
                grid[i][j] = 0;
            }
            else
            {
                grid[i][j] = 1;
            }
        }
    }
    grid[p][q] = 0;

    // last sample points have no neighbors below / to the right, so we use pixels on the
    // last row / column of the input image for them
    for (int i = 0; i < p; i++)
    {
        ppm_pixel curr_pixel = image->data[i * step_x * image->y + image->x - 1];
        // se itereaza prin matrice, folosind stepX pentru a trece de la pixel la pixel
        unsigned char curr_color = (curr_pixel.red + curr_pixel.green + curr_pixel.blue) / 3;

        if (curr_color > sigma)
        {
            grid[i][q] = 0;
        }
        else
        {
            grid[i][q] = 1;
        }
    }
    for (int j = 0; j < q; j++)
    {
        ppm_pixel curr_pixel = image->data[(image->x - 1) * image->y + j * step_y];

        unsigned char curr_color = (curr_pixel.red + curr_pixel.green + curr_pixel.blue) / 3;

        if (curr_color > sigma)
        {
            grid[p][j] = 0;
        }
        else
        {
            grid[p][j] = 1;
        }
    }

    return grid;
}

// Corresponds to step 2 of the marching squares algorithm, which focuses on identifying the
// type of contour which corresponds to each subgrid. It determines the binary value of each
// sample fragment of the original image and replaces the pixels in the original image with
// the pixels of the corresponding contour image accordingly.
void march(ppm_image *image, unsigned char **grid, ppm_image **contour_map, int step_x, int step_y)
{
    int p = image->x / step_x;
    int q = image->y / step_y;

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < q; j++)
        {
            unsigned char k = 8 * grid[i][j] + 4 * grid[i][j + 1] + 2 * grid[i + 1][j + 1] + 1 * grid[i + 1][j];
            update_image(image, contour_map[k], i * step_x, j * step_y);
        }
    }
}

// Calls `free` method on the utilized resources.
void free_resources(ppm_image *image, ppm_image **contour_map, unsigned char **grid, int step_x)
{
    for (int i = 0; i < CONTOUR_CONFIG_COUNT; i++)
    {
        free(contour_map[i]->data);
        free(contour_map[i]);
    }
    free(contour_map);

    for (int i = 0; i <= image->x / step_x; i++)
    {
        free(grid[i]);
    }
    free(grid);

    free(image->data);
    free(image);
}
void *rescale_image(void *arg)
{
    uint8_t sample[3];
    struct bic_int *img = (struct bic_int *)arg;
    long id = img->id;
    int start = id * (double)img->new_image->x / img->P;
    int end = min((id + 1) * (double)img->new_image->x / img->P, img->new_image->x);
    // we only rescale downwards

    // use bicubic interpolation for scaling
    for (int i = start; i < end; i++)
    {
        for (int j = 0; j < img->new_image->y; j++)
        {
            float u = (float)i / (float)(img->new_image->x - 1);
            float v = (float)j / (float)(img->new_image->y - 1);
            sample_bicubic(img->image, u, v, sample);

            img->new_image->data[i * img->new_image->y + j].red = sample[0];
            img->new_image->data[i * img->new_image->y + j].green = sample[1];
            img->new_image->data[i * img->new_image->y + j].blue = sample[2];
        }
    }
    free(img);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        fprintf(stderr, "Usage: ./tema1 <in_file> <out_file> <P>\n");
        return 1;
    }

    ppm_image *image = read_ppm(argv[1]);
    int step_x = STEP;
    int step_y = STEP;

    // 0. Initialize contour map
    ppm_image **contour_map = init_contour_map();

    // 1. Rescale the image

    int x, id;
    void *status;
    int num_threads = atoi(argv[3]);
    long ids[num_threads];

    pthread_t threads[num_threads];

    // alloc memory for image
    ppm_image *new_image = (ppm_image *)malloc(sizeof(ppm_image));
    if (!new_image)
    {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    new_image->x = RESCALE_X;
    new_image->y = RESCALE_Y;

    new_image->data = (ppm_pixel *)malloc(new_image->x * new_image->y * sizeof(ppm_pixel));
    if (!new_image)
    {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    if (image->x <= RESCALE_X && image->y <= RESCALE_Y)
        new_image = image;
    else
    {

        for (id = 0; id < num_threads; id++)
        {
            struct bic_int *img;
            img = malloc(sizeof(struct bic_int));
            img->P = num_threads;
            img->image = image;
            img->new_image = new_image;
            ids[id] = id;
            img->id = ids[id];

            x = pthread_create(&threads[id], NULL, rescale_image, img);

            if (x)
            {
                printf("Eroare la crearea thread-ului %d\n", id);
                exit(-1);
            }
        }

        for (id = 0; id < num_threads; id++)
        {
            x = pthread_join(threads[id], &status);

            if (x)
            {
                printf("Eroare la asteptarea thread-ului %d\n", id);
                exit(-1);
            }
        }
        free(image->data);
        free(image);
    }

    // free(img->image->data);
    // free(img->image);

    // 2. Sample the grid
    unsigned char **grid = sample_grid(new_image, step_x, step_y, SIGMA);

    // 3. March the squares
    march(new_image, grid, contour_map, step_x, step_y);

    // 4. Write output
    write_ppm(new_image, argv[2]);

    free_resources(new_image, contour_map, grid, step_x);

    return 0;
}
