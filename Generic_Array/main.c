
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <inttypes.h>
void insert(char *sir, data_structure *structura)
{
	char *token, *pers1, *pers2;
	int i;
	int banc1 = 0, banc2 = 0;
	int8_t banc1_int8, banc2_int8;
	int16_t banc1_int16;
	int32_t banc1_int32, banc2_int32;
	token = strtok(sir, " ");
	// printf("%s\n", token);
	token = strtok(NULL, " ");
	structura->header->type = token[0];
	// printf("%c\n", structura->header->type);
	token = strtok(NULL, " ");
	pers1 = malloc(strlen(token) + 1);
	strcpy(pers1, token);
	// printf("%s\n", pers1);
	token = strtok(NULL, " ");
	if (token[0] != '-')
		for (i = 0; i < strlen(token); i++)
			banc1 = banc1 * 10 + (token[i] - '0');
	else
	{
		for (i = 1; i < strlen(token); i++)
			banc1 = banc1 * 10 + (token[i] - '0');
		banc1 = (-1) * banc1;
	}
	// printf("banc1=%d\n", banc1);
	token = strtok(NULL, " ");
	if (token[0] != '-')
		for (i = 0; i < strlen(token); i++)
			banc2 = banc2 * 10 + (token[i] - '0');
	else
	{
		for (i = 1; i < strlen(token); i++)
			banc2 = banc2 * 10 + (token[i] - '0');
		banc2 = (-1) * banc2;
	}
	// printf("banc2=%d\n", banc2);
	token = strtok(NULL, " ");
	pers2 = malloc(strlen(token) + 1);
	strcpy(pers2, token);
	// printf("%s\n", pers2);
	if (structura->header->type == '1')
	{
		banc1_int8 = banc1;
		banc2_int8 = banc2;
		structura->data = malloc(sizeof(banc1_int8) + sizeof(banc2_int8) + strlen(pers1) + 1 + strlen(pers2) + 1);
		structura->header->len = sizeof(banc1_int8) + sizeof(banc2_int8) + strlen(pers1) + 1 + strlen(pers2) + 1;
		memcpy(structura->data, pers1, strlen(pers1) + 1);
		memcpy(structura->data + strlen(pers1) + 1, &banc1_int8, sizeof(banc1_int8));
		memcpy(structura->data + strlen(pers1) + 1 + sizeof(banc1_int8), &banc2_int8, sizeof(banc2_int8));
		memcpy(structura->data + strlen(pers1) + 1 + sizeof(banc1_int8) + sizeof(banc2_int8), pers2, strlen(pers2) + 1);
	}
	else if (structura->header->type == '2')
	{
		banc1_int16 = banc1;
		banc2_int32 = banc2;
		structura->data = malloc(sizeof(banc1_int16) + sizeof(banc2_int32) + strlen(pers1) + 1 + strlen(pers2) + 1);
		structura->header->len = sizeof(banc1_int16) + sizeof(banc2_int32) + strlen(pers1) + 1 + strlen(pers2) + 1;
		memcpy(structura->data, pers1, strlen(pers1) + 1);
		memcpy(structura->data + strlen(pers1) + 1, &banc1_int16, sizeof(banc1_int16));
		memcpy(structura->data + strlen(pers1) + 1 + sizeof(banc1_int16), &banc2_int32, sizeof(banc2_int32));
		memcpy(structura->data + strlen(pers1) + 1 + sizeof(banc1_int16) + sizeof(banc2_int32), pers2, strlen(pers2) + 1);
	}
	else if (structura->header->type == '3')
	{
		banc1_int32 = banc1;
		banc2_int32 = banc2;
		structura->data = malloc(sizeof(banc1_int32) + sizeof(banc2_int32) + strlen(pers1) + 1 + strlen(pers2) + 1);
		structura->header->len = sizeof(banc1_int32) + sizeof(banc2_int32) + strlen(pers1) + 1 + strlen(pers2) + 1;
		// printf("deci %d\n",structura->header->len);
		memcpy(structura->data, pers1, strlen(pers1) + 1);
		memcpy(structura->data + strlen(pers1) + 1, &banc1_int32, sizeof(banc1_int32));
		memcpy(structura->data + strlen(pers1) + 1 + sizeof(banc1_int32), &banc2_int32, sizeof(banc2_int32));
		memcpy(structura->data + strlen(pers1) + 1 + sizeof(banc1_int32) + sizeof(banc2_int32), pers2, strlen(pers2) + 1);
	}
	free(pers1);
	free(pers2);
}

int add_last(void **arr, int *len, data_structure *data)
{
	int i = 0, nr_oct = 0;
	head *aux = malloc(sizeof(head));
	for (i = 0; i < *len; i++)
	{
		memcpy(aux, *arr + nr_oct, sizeof(head));
		nr_oct = nr_oct + sizeof(head) + aux->len;
	}

	if (*arr != NULL)
		*arr = realloc(*arr, sizeof(head) + data->header->len + nr_oct);
	else
		*arr = malloc(sizeof(head) + data->header->len);
	if (*arr == NULL)
		return 1;

	memcpy(*arr + nr_oct, data->header, sizeof(head));
	memcpy(*arr + nr_oct + sizeof(head), data->data, data->header->len);
	*len += 1;
	free(data->data);
	free(aux);
	return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{
	int i = 0, nr_oct = 0, nr_tot_oct = 0;
	head *aux = malloc(sizeof(head));

	for (i = 0; i < index; i++)
	{
		memcpy(aux, *arr + nr_oct, sizeof(head));
		nr_oct = nr_oct + sizeof(head) + aux->len;
	}

	for (i = 0; i < *len; i++)
	{
		memcpy(aux, *arr + nr_tot_oct, sizeof(head));
		nr_tot_oct = nr_tot_oct + sizeof(head) + aux->len;
	}

	*arr = realloc(*arr, nr_tot_oct + sizeof(head) + data->header->len);
	memcpy(*arr + nr_oct + data->header->len + sizeof(head), *arr + nr_oct, nr_tot_oct - nr_oct);
	memcpy(*arr + nr_oct, data->header, sizeof(head));
	memcpy(*arr + nr_oct + sizeof(head), data->data, data->header->len);
	*len += 1;
	free(data->data);
	free(aux);
	return 0;
}
int delete_at(void **arr, int *len, int index)
{ /*
	 int d = 0;
	 d = *len;
	  printf("len %d\n", d); */
	// printf("index: %d \n", index);
	int i = 0, nr_oct = 0, nr_oct_del = 0, nr_tot_oct = 0;
	head *aux = malloc(sizeof(head));
	for (i = 0; i < *len; i++)

	{

		memcpy(aux, *arr + nr_tot_oct, sizeof(head));
		nr_tot_oct = nr_tot_oct + sizeof(head) + aux->len;
	}
	if (*len >= 1)
		if (index <= *len)
		{
			for (i = 0; i < index; i++)

			{
				// printf("i: %d \n", i);
				memcpy(aux, *arr + nr_oct, sizeof(head));
				nr_oct = nr_oct + sizeof(head) + aux->len;
				// printf("elem %d\n", i );
				// printf("nr oct %d\n", nr_oct);
			}
			memcpy(aux, *arr + nr_oct, sizeof(head));
			nr_oct_del = nr_oct + sizeof(head) + aux->len;
			// printf("nr oct del %d\n", nr_oct_del);
			memmove(*arr + nr_oct, *arr + nr_oct_del, nr_tot_oct - nr_oct_del);
		}
	*arr = realloc(*arr, nr_tot_oct-nr_oct_del+nr_oct);
	*len -= 1;
	free(aux);
	return 0;
}

void print(void *arr, int len)
{
	head *header;
	char *pers1, *pers2;
	int8_t banc1_8 = 0, banc2_8 = 0;
	int16_t banc1_16 = 0;
	int32_t banc1_32 = 0, banc2_32 = 0;
	header = malloc(sizeof(head));
	int i = 0, nr_oct = 0;

	for (i = 0; i < len; i++)
	{
		memcpy(header, arr + nr_oct, sizeof(head));

		if (header->type == '1')
		{
			printf("Tipul %c\n", header->type);
			pers1 = arr + nr_oct + sizeof(head);
			printf("%s pentru ", pers1);
			memcpy(&banc1_8, arr + nr_oct + sizeof(head) + strlen(pers1) + 1, sizeof(int8_t));
			memcpy(&banc2_8, arr + nr_oct + sizeof(head) + strlen(pers1) + 1 + sizeof(banc1_8), sizeof(int8_t));
			pers2 = arr + nr_oct + sizeof(head) + strlen(pers1) + 1 + sizeof(banc1_8) + sizeof(banc2_8);
			printf("%s\n", pers2);
			printf("%d\n", banc1_8);
			// printf("%"PRId8"\n", banc1_8);
			printf("%d\n\n", banc2_8);
			nr_oct += sizeof(head) + strlen(pers1) + 1 + sizeof(banc1_8) + sizeof(banc2_8) + strlen(pers2) + 1;
		}
		if (header->type == '2')
		{
			printf("Tipul %c\n", header->type);
			pers1 = arr + nr_oct + sizeof(head);
			printf("%s pentru ", pers1);
			memcpy(&banc1_16, arr + nr_oct + sizeof(head) + strlen(pers1) + 1, sizeof(int16_t));
			memcpy(&banc2_32, arr + nr_oct + sizeof(head) + strlen(pers1) + 1 + sizeof(banc1_16), sizeof(int32_t));
			pers2 = arr + nr_oct + sizeof(head) + strlen(pers1) + 1 + sizeof(banc1_16) + sizeof(banc2_32);
			printf("%s\n", pers2);
			printf("%d\n", banc1_16);
			printf("%d\n\n", banc2_32);
			nr_oct += sizeof(head) + strlen(pers1) + 1 + sizeof(banc1_16) + sizeof(banc2_32) + strlen(pers2) + 1;
		}
		if (header->type == '3')
		{
			printf("Tipul %c\n", header->type);
			pers1 = arr + nr_oct + sizeof(head);
			printf("%s pentru ", pers1);
			memcpy(&banc1_32, arr + nr_oct + sizeof(head) + strlen(pers1) + 1, sizeof(int32_t));
			memcpy(&banc2_32, arr + nr_oct + sizeof(head) + strlen(pers1) + 1 + sizeof(int32_t), sizeof(int32_t));
			pers2 = arr + nr_oct + sizeof(head) + strlen(pers1) + 1 + sizeof(int32_t) + sizeof(banc2_32);
			printf("%s\n", pers2);
			printf("%d\n", banc1_32);
			printf("%d\n\n", banc2_32);
			nr_oct += sizeof(head) + strlen(pers1) + 1 + sizeof(int32_t) + sizeof(banc2_32) + strlen(pers2) + 1;
		}
	}
	free(header);
}

void find(void *data_block, int len, int index)
{
	char *pers1, *pers2;
	int8_t banc1_8 = 0, banc2_8 = 0;
	int16_t banc1_16 = 0;
	int32_t banc1_32 = 0, banc2_32 = 0;
	head *aux = malloc(sizeof(head));
	int nr_oct = 0, i;
	for (i = 0; i < index; i++)
	{
		memcpy(aux, data_block + nr_oct, sizeof(head));
		nr_oct = nr_oct + sizeof(head) + aux->len;
	}
	memcpy(aux, data_block + nr_oct, sizeof(head));

	if (aux->type == '1')
	{
		printf("Tipul %c\n", aux->type);
		pers1 = data_block + nr_oct + sizeof(head);
		printf("%s pentru ", pers1);
		memcpy(&banc1_8, data_block + nr_oct + sizeof(head) + strlen(pers1) + 1, sizeof(int8_t));
		memcpy(&banc2_8, data_block + nr_oct + sizeof(head) + strlen(pers1) + 1 + sizeof(banc1_8), sizeof(int8_t));
		pers2 = data_block + nr_oct + sizeof(head) + strlen(pers1) + 1 + sizeof(banc1_8) + sizeof(banc2_8);
		printf("%s\n", pers2);
		printf("%d\n", banc1_8);
		// printf("%"PRId8"\n", banc1_8);
		printf("%d\n\n", banc2_8);
		nr_oct += sizeof(head) + strlen(pers1) + 1 + sizeof(banc1_8) + sizeof(banc2_8) + strlen(pers2) + 1;
	}
	if (aux->type == '2')
	{
		printf("Tipul %c\n", aux->type);
		pers1 = data_block + nr_oct + sizeof(head);
		printf("%s pentru ", pers1);
		memcpy(&banc1_16, data_block + nr_oct + sizeof(head) + strlen(pers1) + 1, sizeof(int16_t));
		memcpy(&banc2_32, data_block + nr_oct + sizeof(head) + strlen(pers1) + 1 + sizeof(banc1_16), sizeof(int32_t));
		pers2 = data_block + nr_oct + sizeof(head) + strlen(pers1) + 1 + sizeof(banc1_16) + sizeof(banc2_32);
		printf("%s\n", pers2);
		printf("%d\n", banc1_16);
		printf("%d\n\n", banc2_32);
		nr_oct += sizeof(head) + strlen(pers1) + 1 + sizeof(banc1_16) + sizeof(banc2_32) + strlen(pers2) + 1;
	}
	if (aux->type == '3')
	{
		printf("Tipul %c\n", aux->type);
		pers1 = data_block + nr_oct + sizeof(head);
		printf("%s pentru ", pers1);
		memcpy(&banc1_32, data_block + nr_oct + sizeof(head) + strlen(pers1) + 1, sizeof(int32_t));
		memcpy(&banc2_32, data_block + nr_oct + sizeof(head) + strlen(pers1) + 1 + sizeof(int32_t), sizeof(int32_t));
		pers2 = data_block + nr_oct + sizeof(head) + strlen(pers1) + 1 + sizeof(int32_t) + sizeof(banc2_32);
		printf("%s\n", pers2);
		printf("%d\n", banc1_32);
		printf("%d\n\n", banc2_32);
		nr_oct += sizeof(head) + strlen(pers1) + 1 + sizeof(int32_t) + sizeof(banc2_32) + strlen(pers2) + 1;
	}
	free(aux);
}
int main()
{
	data_structure *structura;
	structura = malloc(sizeof(data_structure));
	structura->header = malloc(sizeof(head));
	void *arr = NULL;
	int len = 0, index, indice;
	char *sir, *token, *copiesir = NULL;
	char *aux;
	sir = malloc(256 * sizeof(char));
	// printf("Dati sir: ");
	fgets(sir, 256, stdin);
	sir[strlen(sir) - 1] = '\0';
	while (strcmp(sir, "exit") != 0)
	{
		copiesir = malloc(strlen(sir) + 1);
		strcpy(copiesir, sir);
		token = strtok(sir, " ");
		if (strcmp(token, "insert") == 0)
		{
			insert(copiesir, structura);
			add_last(&arr, &len, structura);
		}
		else if (strcmp(token, "print") == 0)
			print(arr, len);
		else if (strcmp(token, "delete_at") == 0)
		{
			index = 0;
			aux = strtok(NULL, " ");
			// index = aux[0];
			index = index * 10 + (aux[0] - '0');
			// printf("index:%d\n", index);
			delete_at(&arr, &len, index);
		}
		else if (strcmp(token, "insert_at") == 0)
		{
			indice = 0;
			aux = strtok(NULL, " ");
			indice = indice * 10 + (aux[0] - '0');
			// printf("indice %d \n", indice);
			insert(copiesir + 10, structura);
			if (indice >= len)
				add_last(&arr, &len, structura);
			else
				add_at(&arr, &len, structura, indice);
		}
		else if (strcmp(token, "find") == 0)

		{
			indice = 0;
			aux = strtok(NULL, " ");
			indice = indice * 10 + (aux[0] - '0');
			// printf("indice %d \n", indice);

			find(arr, len, indice);
		}
		// printf("Dati sir: ");
		fgets(sir, 256, stdin);
		sir[strlen(sir) - 1] = '\0';
		free(copiesir);
	}
	free(structura->header);
	free(structura);
	free(arr);
	free(sir);

	return 0;
}