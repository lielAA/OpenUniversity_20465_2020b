/*Author: Liel Adir
  Student ID: 20-280253
  Date: 10/05/2020
  
 						####### Program Description #######
   This program is represent a tree - each node in the matrix get index name from 0 up to N-1.
   This tree represented by 2D array (matrix) by size of NxN, this matrix values received 0 OR 1.
   if matrix index == 1 --> there is straight connection between u to v nodes (u is the father of v in the tree).
   if matrix index == 0 --> there is NO straight connection between u to v node.
   adjacency program include main method that received from the user 2D array (Matrix) of adjmat type, by size of NxN and print it. 
   In addition received from the user two node from the tree (u,v) and return TRUE if there is path from those two nodes 
   and FALSE if there is NOT */
#include "adjacency.h"

int main()
{
    int u, v;/*u = row in matrix ; v = column in matrix*/
    adjmat A; 
    bool b;/*variable save the return bool value from path method*/
    inputMatrix(A); /*Received A matrix from the user*/
    outputMatrix(A);/*Print Matrix*/

    printf("\nPlease insert two numbers with Enter between them, that represent path from 1st node to 2nd node in matrix\n\n");
    while (scanf("%d %d", &u, &v) == 2 && (!(u == -1 && v == -1)))/*Continue receive path from the user till insert -1 -1*/
    {
        b = path(A, u, v);
        if (b == FALSE) 
        {
            printf("There is No path from %d to %d in your tree\n", u, v);
        }
        else
        {
            printf("There is a path from %d to %d in your tree\n", u, v);
        }
        printf("\nPlease insert another two numbers:\n");
    }
    return 0;
}
                    /*##### Method Description #####
        Received from the user, matrix A[N][N] with 0 OR 1 values*/
void inputMatrix(adjmat A)
{
    int u, v;/*u = row in matrix ; v = column in matrix*/
    printf("\nPlease enter values for matrix by [%d][%d], after any value press Enter.\n", N, N);
    for (u = 0; u < N; u++) /*represent row in matrix*/
    {
        for (v = 0; v < N; v++) /*represent column in matrix*/
        {
            printf("matrix value: [%d][%d]: \n", u, v);
            scanf("%u", &A[u][v]);/*Received value to matrix A[u][v]*/
        }
    }
}
                    /* #####Method Description #####
                Print matrix A[N][N] with border values*/
void outputMatrix(adjmat A)
{
    int u, v;/*u = row in matrix ; v = column in matrix*/
    printf("\n\nYour matrix is:\n\n    ");
    for (u = 0; u < N; u++)
    {
        printf("  %d", u); /*print upper border matrix line */
    }
    printf("\n    ");
    for (u = 0; u < N; u++)/*under any number for upper border line - print "overline" symbol*/
    {
        if (u > 9)
        {
            printf("  ‾‾");/*for double digit print double "overline"*/
        }
        else
        {
            printf("  ‾");/*for single digit print single "overline"*/
        }
    }

    for (u = 0; u < N; u++)
    {
        if (u > 9)
        {
            printf("\n%d| ", u);/*for double digit */
        }
        else
        {
            printf("\n%d|  ", u);/*for single digit */
        }
        for (v = 0; v < N; v++)/*printing matrix values*/
        {
            if (v > 9)
            {
                printf("   %d", A[u][v]);/*for double digit */
            }
            else
            {
                printf("  %d", A[u][v]);/*for single digit */
            }
        }
        printf("\n");
    }
}
                            /* #####Method Description #####
        path method received A[N][N] matrix, u and v indexes  that represent two node from the tree (u,v)
        and return TRUE if there is path from those two node and FALSE if there is NOT*/
bool path(adjmat A, int u, int v)
{
    int i, j; /*represent row and column in matrix*/
    int row = INT_MAX;/*variable save father we found in tree*/
    if (u > N - 1 || v > N - 1)/*if path index is out of matrix sizes*/
    {
        return FALSE;
    }
    else if (u == v)/*if path is node to itself (u==1 ; v==1)*/
    {
        return TRUE;
    }
    else
    {
        for (j = 0; j < N; j++)
        {
            for (i = 0; i < N; i++)
            {
                if (j != 0 && row != INT_MAX)/*if we found at least one father && row is changed from INT_MAX*/
                {
                    if (A[i][row] == 1)/*father is found*/
                    {
                        row = i;
                    }
                }
                else if (A[i][v] == 1)/*if we found father*/
                {
                    row = i;
                }
                if (u == row)/*if we found that the intended father equal to that we catch by seraching above*/
                {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}