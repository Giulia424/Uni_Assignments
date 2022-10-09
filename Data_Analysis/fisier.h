#ifndef STDIO_H
#include<stdio.h>
#endif

#ifndef STDLIB_H
#include<stdlib.h>
#endif
#ifndef MATH_H
#include<math.h>
#endif

#ifndef STRING_H
#include<string.h>
#endif


typedef struct Nod
{int timestamp;
double value;
struct Nod *ant;
struct Nod *urm;
}nod;

typedef struct
{int nr;
struct Nod *prim;
struct Nod *ultim;
}capete;


