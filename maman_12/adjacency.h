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

#include <stdio.h>
#define N 5/*matrix size A[N][N]*/
#define INT_MAX 2147483647/*max integer value for 'row' variable in path method*/

typedef enum{FALSE,TRUE} bool;/*FALSE = 0 ; TRUE = 1 --> bool type of enum*/
typedef bool adjmat[N][N];/*matrix adjmat[N][N] type of bool*/

                            /* ##### Method Description #####
        Received from the user matrixA[N][N] size with 0 OR 1 values*/
void inputMatrix(adjmat);
                            /* #####Method Description #####
        Print matrix A[N][N] with border values*/
void outputMatrix(adjmat);
                            /* #####Method Description #####
        path method received A[N][N] matrix, u and v indexes  that represent two node from the tree (u,v)
        and return TRUE if there is path from those two node and FALSE if there is NOT*/
bool path(adjmat A,int,int);