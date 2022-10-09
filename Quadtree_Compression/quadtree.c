#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include<math.h>

typedef struct QuadtreeNode
{
    unsigned char blue, green, red;
    uint32_t area;
    int32_t top_left, top_right;
    int32_t bottom_left, bottom_right;
} __attribute__((packed)) QuadtreeNode;

typedef struct Tree
{
    uint32_t area;
    unsigned char blue, green, red;
    struct Tree *top_left, *top_right, *bottom_left, *bottom_right;
} arb;

typedef struct pixel
{
    unsigned char blue, green, red;
} pix;

void citire(pix **p, int width, int height, char *nume, int c)
{
    int i, j;
    FILE *fisier;
    fisier = fopen(nume, "rb");
    if (fisier == NULL)
    {
        printf("Error!");
        exit(1);
    }

    // printf("%d", width);
    fseek(fisier, c, SEEK_SET);

    for (i = 0; i < width; i++)
        for (j = 0; j < height; j++)
        {
            p[i][j].red = fgetc(fisier);
            // c += sizeof(p[i][j].red);
            // fseek(fisier, c, SEEK_SET);
            p[i][j].green = fgetc(fisier);
            // c += sizeof(p[i][j].green);
            // fseek(fisier, c, SEEK_SET);
            p[i][j].blue = fgetc(fisier);
            // c += sizeof(p[i][j].blue);
            // fseek(fisier, c, SEEK_SET);
        }
    fclose(fisier);
    /*     for (int i = 0; i < width; i++)
            for (int j = 0; j < height; j++)
            {
                printf("%d\n", p[i][j].red);
                printf("%d\n", p[i][j].green);
                printf("%d\n", p[i][j].blue);
            } */
}
void creare_arb(pix **p, arb *tree, int x, int y, int length, int prag, uint32_t *nr_cul, uint32_t *nr_nod)
{
    int i, j;
    long red_med = 0, green_med = 0, blue_med = 0;
    long mean = 0, div = 3 * length * length;
    tree->top_left = tree->top_right = tree->bottom_left = tree->bottom_right = NULL;
    for (i = x; i < x + length; i++)
        for (j = y; j < y + length; j++)
        {
            red_med += p[i][j].red;
            green_med += p[i][j].green;
            blue_med += p[i][j].blue;
        }
    tree->area = length * length;
    red_med = red_med / (length * length);
    green_med = green_med / (length * length);
    blue_med = blue_med / (length * length);
    // printf("red:%ld\n", red_med);
    // printf("green:%ld\n", green_med);
    // printf("blue:%ld\n", blue_med);
    for (i = x; i < x + length; i++)
        for (j = y; j < y + length; j++)
            mean += (red_med - p[i][j].red) * (red_med - p[i][j].red) + (green_med - p[i][j].green) * (green_med - p[i][j].green) + (blue_med - p[i][j].blue) * (blue_med - p[i][j].blue);
    mean = mean / div;
    // printf("mean:%f\n", mean);
    // printf("area:%d\n", tree->area);
    tree->red = red_med;
    tree->green = green_med;
    tree->blue = blue_med;
    if (mean > prag)
    {
        *nr_nod += 4;
        tree->top_left = malloc(sizeof(arb));
        creare_arb(p, tree->top_left, x, y, length / 2, prag, nr_cul, nr_nod);
        tree->top_right = malloc(sizeof(arb));
        creare_arb(p, tree->top_right, x, y + length / 2, length / 2, prag, nr_cul, nr_nod);
        tree->bottom_left = malloc(sizeof(arb));
        creare_arb(p, tree->bottom_left, x + length / 2, y, length / 2, prag, nr_cul, nr_nod);
        tree->bottom_right = malloc(sizeof(arb));
        creare_arb(p, tree->bottom_right, x + length / 2, y + length / 2, length / 2, prag, nr_cul, nr_nod);
    }
    else
        *nr_cul += 1;
}
void compresie(arb *tree, QuadtreeNode *v, uint32_t nr_nod, int *x)
{
    int k = *x;
    v[*x].area = tree->area;
    v[*x].red = tree->red;
    v[*x].green = tree->green;
    v[*x].blue = tree->blue;
    if (tree->top_left != NULL)
    {
        v[k].top_left = *(x) + 1;
        *(x) += 1;
        compresie(tree->top_left, v, nr_nod, x);
        v[k].top_right = *(x) + 1;
        *(x) += 1;
        compresie(tree->top_right, v, nr_nod, x);
        v[k].bottom_right = *(x) + 1;
        *(x) += 1;
        compresie(tree->bottom_right, v, nr_nod, x);
        v[k].bottom_left = *(x) + 1;
        *(x) += 1;
        compresie(tree->bottom_left, v, nr_nod, x);
    }
    else
    {
        v[*x].top_left = -1;
        v[*x].top_right = -1;
        v[*x].bottom_right = -1;
        v[*x].bottom_left = -1;
    }
    // compresie(tree, v, nr_nod, x + 1);
}
int nr_cifre(int nr)
{
    int nr_c = 0;
    do
    {
        nr = nr / 10;
        nr_c++;
    } while (nr);
    return nr_c;
}

void eliberare(arb *tree)
{
    if (tree->top_left != NULL)
    {
        eliberare(tree->top_left);
        eliberare(tree->top_right);
        eliberare(tree->bottom_right);
        eliberare(tree->bottom_left);
    }
    free(tree);
}

int main(int argc, char **argv)
{
    uint32_t nr_culori = 0, nr_noduri = 1;
    int c = 0;
    char type[3];
    int valmax, i, prag = 0, x = 0;
    int width, height;
    arb *root = NULL;
    root = malloc(sizeof(arb));
    QuadtreeNode *v;
    FILE *fisier;
    fisier = fopen(argv[3], "r");
    if (fisier == NULL)
    {
        printf("Error!");
        exit(1);
    }
    fscanf(fisier, "%s %d %d %d", type, &width, &height, &valmax);
    fclose(fisier);
    c = strlen(type) + nr_cifre(width) + nr_cifre(height) + nr_cifre(valmax) + 4;
    // printf("c: %d\n",c);
    pix **p;
    p = malloc(sizeof(pix *) * height);
    for (i = 0; i < width; i++)
        *(p + i) = malloc(width * sizeof(pix));

    if (strcmp(argv[1], "-c") == 0)
    {
        // printf("%ld\n", strlen(argv[2]));
        for (i = 0; i < strlen(argv[2]); i++)
            prag = 10 * prag + (argv[2][i] - '0');
        // printf("%d\n", prag);
    }
    FILE *fis;
    fis = fopen(argv[4], "wb");
    // else if(strcmp(argv[1]=="-d")
    // else if(strcmp(argv[1]=="-m")
    citire(p, width, height, argv[3], c);
    creare_arb(p, root, 0, 0, width, prag, &nr_culori, &nr_noduri);
    v = malloc(nr_noduri * sizeof(QuadtreeNode));
    // printf("nr noduri %u\n",nr_noduri);
    // printf("nr culori %u\n",nr_culori);
    compresie(root, v, nr_noduri, &x);
    fwrite(&nr_culori, sizeof(uint32_t), 1, fis);
    fwrite(&nr_noduri, sizeof(uint32_t), 1, fis);
    fwrite(v, sizeof(QuadtreeNode), nr_noduri, fis);
    fclose(fis);
    free(v);
    for (i = 0; i < height; i++)
        free(p[i]);
    free(p);
    eliberare(root);

    return 0;
}