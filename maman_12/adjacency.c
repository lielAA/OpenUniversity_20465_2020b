#include "adjacency.h"
/*#include <stdio.h>
#define N 3

typedef enum{false,true} bool;
typedef bool adjmat[N][N];
adjmat A;

void inputMatrix();
void outputMatrix();
bool path(adjmat A,int,int);*/

int main()
{
    int u,v;
    bool b;
    inputMatrix();
    outputMatrix();
    

    printf("\nPlease insert two numbers with Enter between them, that represent path from 1st num to 2nd num in matrix\n");
	while(scanf("%d %d",&u,&v) == 2 && (!(u==-1 && v==-1)))
    {
        if(u > N-1 || v > N-1)
            printf("There is No path from %d to %d in your tree\n",u,v);
        else if(u == v)
        {
            printf("There is a path from %d to %d in your tree\n",u,v);            
        }
        else
        {
            b = path(A,u,v);
            if(b == false)
                printf("There is No path from %d to %d in your tree\n",u,v);
            else
                printf("There is a path from %d to %d in your tree\n",u,v);
       
        }
        printf("\nPlease insert another two numbers:\n");
    }    
    return 0;
}

void inputMatrix() 
{
    int u, v;
    printf("\nPlease enter values for matrix by [%d][%d], after any value press Enter.\n", N, N);
    for (u = 0; u < N; u++)
    {
        for (v = 0; v < N; v++)
        {
            printf("matrix value: [%d][%d]: \n", u, v);
            scanf("%u",&A[u][v]); 
        }
    }
}

void outputMatrix()
{
    int u,v;
    printf("\n\nYour matrix is:\n\n    ");
    for (u = 0; u < N; u++)
        printf("  %d", u);
    printf("\n    ");
    for (u = 0; u < N; u++)
        printf("  ‾");
    for (u = 0; u < N; u++)
    {
        printf("\n%d|  ", u);
        for (v = 0; v < N; v++)
        {
            printf("  %d", A[u][v]);
        }
        printf("\n");
    } 
}

bool path(adjmat A,int u,int v)
{
    /*bool b = false;*/
    printf("\nu = %d ; v=%d\n",u,v);
    if(v > N-1 || v < 0)
        return false;
    if(u > N-1 || u < 0)
        return true;    
    if(A[u][v] == 1)          
        return path(A,u+1,v) || path(A,u-1,v);
    return path(A,u,v+1) && path(A,u,v-1);


    /*if(A[u][v] == 0)          
        return path(A,u+1,v) || path(A,u-1,v);
    return path(A,u,v+1) && path(A,u,v-1);*/
    
}