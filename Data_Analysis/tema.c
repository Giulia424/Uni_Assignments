#include "fisier.h"

void adaugare(capete *lista, int timestp, double val)
{
    nod *celula;
    celula = malloc(sizeof(nod));
    celula->value = val;
    celula->timestamp = timestp;
    celula->ant = lista->ultim;
    celula->urm = NULL;
    if (lista->prim != NULL)
        lista->ultim->urm = celula;
    else
        lista->prim = celula;
    lista->ultim = celula;
}

void eliminare(capete *lista, nod *x)
{
    if (x->ant == NULL)
        if (x->urm == NULL)
            return;
        else
        {
            lista->prim = x->urm;
            x->urm->ant = NULL;
        }
    else if (x->urm == NULL)
    {
        lista->ultim = x->ant;
        x->ant->urm = NULL;
    }
    else
    {
        x->ant->urm = x->urm;
        x->urm->ant = x->ant;
    }
    lista->nr--;
    free(x);
}

void citire(capete *lista)
{
    int i, timestp;
    double val;
    /*     printf("Dati nr de noduri: "); */
    scanf("%d", &lista->nr);
    for (i = 0; i < lista->nr; i++)
    {
        // printf("Dati  timestamp: ");
        scanf("%d%lf", &timestp, &val);
        // printf("Dati  valoare: ");
        // scanf("%le", &val);
        adaugare(lista, timestp, val);
    }
}

void afisare(capete *lista)
{
    // printf("Numarul de noduri este : %d\n", lista->nr);
    printf("%d\n", lista->nr);
    for (nod *i = lista->prim; i != NULL; i = i->urm)
        printf("%d %0.2lf\n", i->timestamp, i->value);
}

void eliberare(capete *lista, nod *x)
{
    if (x != lista->ultim)
        eliberare(lista, x->urm);
    free(x);
}

void e1(capete *lista, nod *x)
{
    int k = 5;
    nod *i;
    double med = 0, sum = 0, dif = 0, suma = 0, dev = 0;

    for (i = x->ant->ant; i != x->urm->urm->urm; i = i->urm)
        sum += i->value;
    med = sum / k;
    for (i = x->ant->ant; i != x->urm->urm->urm; i = i->urm)
    {
        dif = i->value - med;
        suma += dif * dif;
    }
    dev = sqrt(suma / k);
    /*  printf("suma %lf med %lf dev %lf\n", sum, med, dev); */
    if (x != lista->ultim->ant->ant)
        e1(lista, x->urm);
    if (x->value < (med - dev) || x->value > (med + dev))
        eliminare(lista, x);
}

void e2(capete *lista)
{
    int c = 0;
    capete aux;
    aux.nr = 0;
    aux.prim = aux.ultim = NULL;
    nod *i, *j, *x;
    for (x = lista->prim->urm->urm; x != lista->ultim->ant; x = x->urm)
        for (i = x->ant->ant; i != x->urm->urm->urm; i = i->urm)
        {
            c = 0;
            for (j = x->ant->ant; j != x->urm->urm->urm; j = j->urm)
                if (i->value > j->value)
                    c++;
            if (c == 2)
            {
                aux.nr++;
                adaugare(&aux, x->timestamp, i->value);
            }
        }
    eliberare(lista, lista->prim);
    lista->prim = aux.prim;
    lista->ultim = aux.ultim;
    lista->nr = aux.nr;
}

void e3(capete *lista)
{
    nod *i, *x;
    double med = 0, sum = 0;
    int k = 5;
    capete list;
    list.nr = 0;
    list.prim = list.ultim = NULL;
    for (x = lista->prim->urm->urm; x != lista->ultim->ant; x = x->urm)
    {
        sum = 0;
        for (i = x->ant->ant; i != x->urm->urm->urm; i = i->urm)
            sum += i->value;
        med = sum / k;
        adaugare(&list, x->timestamp, med);
        list.nr++;
    }
    eliberare(lista, lista->prim);
    lista->prim = list.prim;
    lista->ultim = list.ultim;
    lista->nr = list.nr;
}
void u(capete *lista)
{
    double dif;
    nod *x;
    for (x = lista->prim->urm; x != NULL; x = x->urm)
    {
        dif = (x->timestamp - x->ant->timestamp) / 1000.0;
        if (dif >= 0.1 && dif <= 1)
        {
            x->value = (x->ant->value + x->value) / 2.0;
            x->timestamp = (x->ant->timestamp + x->timestamp) / 2;
        }
    }
}

int main(int argc, char **argv)
{
    capete lista;
    int i;
    lista.prim = lista.ultim = NULL;
    citire(&lista);
    for (i = 0; i < argc; i++)
        if (strcmp(argv[i], "--e1") == 0)
            e1(&lista, lista.prim->urm->urm);
        else if (strcmp(argv[i], "--e2") == 0)
            e2(&lista);
        else if (strcmp(argv[i], "--e3") == 0)
            e3(&lista);
        else if (strcmp(argv[i], "--u") == 0)
            u(&lista);
    afisare(&lista);
    eliberare(&lista, lista.prim);
    return 0;
}
