#include "../adjacency.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/*#define N 3

typedef enum{false,true} bool;
typedef bool adjmat[N][N];
adjmat A;
*/
int test_main()
{
    if(N == 2)
    {
        adjmat A [N][N] =
        {
            {0,1},
            {0,0}
        };
        assert(path(A,0,0) == 1);
        printf("All pass");
    }

        
}
