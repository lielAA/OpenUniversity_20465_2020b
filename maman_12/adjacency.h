#include <stdio.h>
#define N 3

typedef enum{FALSE,TRUE} bool;
typedef bool adjmat[N][N];
/*adjmat A;*/

void inputMatrix(adjmat);
void outputMatrix(adjmat);
bool path(adjmat A,int,int);
