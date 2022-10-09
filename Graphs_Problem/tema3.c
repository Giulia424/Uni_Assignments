#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include<math.h>
#define inf 9999
typedef struct Graf
{
    unsigned n, m, d; // n = număr de noduri, m = număr de arce, d= număr de depozite
    double **a;       // adresa matrice de adiacență
} graf;

void print1(int *path, int *invpath,int *len1,int*len2, int x, double drum1, double drum2,double *drum)
{ 
    printf("%d\n",x);
    printf("%.1lf ",drum1);
    printf("%.1lf\n",drum2); 
    for (int i = *len1; i >= 0; i--)
        printf("%d ", path[i]);//aici am afisat drumul parcurs pana de la depozit pana la magazin 
    for (int i = *len2-1; i >= 1; i--)
         printf("%d ",invpath[i]); 
    printf("%d",invpath[0]);//iar aici am afisat drumul de intors, de la magazin la depozit
    printf("\n"); 
    *drum+=drum1;
    *drum+=drum2;
}

void ex1(graf *g, int start, int finnish, int k, int *path, int *len, double *drum) // Dijkstra aparent mersi Abdul
{//am implementat algoritmul functiei Dijkstra
    int i, j, urm, c = 0;
    int *pred, *viz;
    double **cost, *dist, mindist;
    dist = malloc(g->n * sizeof(double));
    pred = malloc(g->n * sizeof(int));
    viz = malloc(g->n * sizeof(int));
    cost = malloc(g->n * (sizeof(double *)));
    for (i = 0; i < g->n; i++)
        cost[i] = malloc(g->n * sizeof(double));
    for (i = 0; i < g->n; i++)
        for (j = 0; j < g->n; j++)
            if (g->a[i][j] == 0)
                cost[i][j] = inf;
            else
                cost[i][j] = g->a[i][j];

    for (i = 0; i < g->n; i++)
    {
        dist[i] = cost[start][i];
        pred[i] = start;
        viz[i] = 0;
    }
    dist[start] = 0;
    viz[start] = 1;

    for (int c = 1; c < g->n - 1; c++)
    {
        mindist = inf;
        for (i = 0; i < g->n; i++)
            if (dist[i] < mindist && !viz[i])
            {
                mindist = dist[i];
                urm = i;
            }
        viz[urm] = 1;
        for (i = 0; i < g->n; i++)
            if (!viz[i])
                if (mindist + cost[urm][i] < dist[i])
                {
                    dist[i] = mindist + cost[urm][i];
                    pred[i] = urm;
                }
    }
    *drum = dist[finnish];//aici am memorat costul distantei de la sursa la destinatie
    i = finnish;
    {   path[c] = i;
        j = i;
        do
        {
            c++;
            j = pred[j];
            path[c] = j;
        } while (j != start);
    }
    *len = c;
    free(dist);
    free(pred);
    free(viz);
    for (i = 0; i < g->n; i++)
        free(cost[i]);
    free(cost);
}

void citire(graf *g, char *c)
{
    int s, k, *x;
    int i,j,a,u, v, *dep, id, nrcer, len1 = 0,len2=0;//id=id-ul magazinului, nrcer=numarul de cerinte,
    //v w, unde u si v sunt ID-urile nodurilor si w este costul parcurgerii drumului dintre acestea
    //dep=vector pentru a retine depozitele
    scanf("%d", &g->n);
    dep = malloc(g->n* sizeof(int));
    x = malloc(g->n * sizeof(int));
    double w, drum1=0, drum2=0,drum=0;
    int *path, *invpath;
    path = malloc(g->n * sizeof(int));
    invpath = malloc(g->n * sizeof(int));
    g->a = malloc(g->n * sizeof(double *));
    for (i = 0; i < g->n; i++)
        g->a[i] = malloc(g->n * sizeof(double));
    scanf("%d", &g->m);
    scanf("%d", &g->d);
    for (i = 0; i < g->n; i++)
         for (j = 0; j < g->n; j++)
            g->a[i][j]=0;
    for (i = 0; i < g->m; i++)
    {
        scanf("%d%d%le", &u, &v, &w);
        g->a[u][v] = w;//aici am creat matricea de costuri asociata grafului
    }
    for (i = 0; i < g->d; i++)
    {
        scanf("%d", &id);
        dep[id] = 1;//aici am creat un vector in care sa pot retine care sunt depozitele
    }
    scanf("%d", &nrcer);
    for(a=0;a<nrcer;a++)
    { 
    scanf("%s", c);
    if (strcmp(c, "e1") == 0)
    {
        if(a!=0)
            {printf("\n");
            drum=0;
            }
        scanf("%d", &s);
        scanf("%d", &k);
        for (int i = 0; i < k; i++)
        {   
            scanf("%d", &x[i]);
            ex1(g, s, x[i], k, path, &len1, &drum1);            
            ex1(g, x[i], s, k, invpath, &len2, &drum2);
            print1(path,invpath, &len1,&len2, x[i], drum1, drum2,&drum);
        }
            printf("%.1lf",drum);
    }
    }
    free(dep);
    free(x);
    free(path);
    free(invpath);
}
void eliberare(graf *g)
{
    int i;
    for (i = 0; i < g->n; i++)
        free(g->a[i]);
    free(g->a);
}
int main()
{
    struct Graf g;
    char *c;
    c = malloc(10*sizeof(char));
    citire(&g, c);
    eliberare(&g);
    free(c);
    return 0;
}