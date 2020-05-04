#include <stdio.h>
#define N 2

typedef enum{false,true} bool;
typedef bool adjmat[N][N];
adjmat A;

void inputMatrix();
void outputMatrix();
bool path(adjmat A,int,int);