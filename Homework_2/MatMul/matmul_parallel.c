/*
**  PROGRAM: Matrix Multiply
**
**  PURPOSE: This is a simple matrix multiply program. 
**           It will compute the product
**
**                C  = A * B
**
**           A and B are set to constant matrices so we
**           can make a quick test of the multiplication.
**  HISTORY: Written by Tim Mattson
*/
#include <malloc.h>
#include <stdio.h>
#include <omp.h>

#define ORDER 50
#define AVAL 3.0
#define BVAL 5.0
#define TOL  0.001

int main(int argc, char **argv)
{
    int Ndim, Pdim, Mdim;   /* A[N][P], B[P][M], C[N][M] */
    int i,j,k;
    double *A, *B, *C, cval, tmp, err, errsq;
    double start_time, run_time;

    Ndim = ORDER;
    Pdim = ORDER*100;
    Mdim = ORDER*100;

    A = (double *)malloc(Ndim*Pdim*sizeof(double));
    B = (double *)malloc(Pdim*Mdim*sizeof(double));
    C = (double *)malloc(Ndim*Mdim*sizeof(double));

    /* Initialize matrices */

    for (i=0; i<Ndim; i++)
        for (j=0; j<Pdim; j++)
            *(A+(i*Ndim+j)) = AVAL;

    for (i=0; i<Pdim; i++)
        for (j=0; j<Mdim; j++)
            *(B+(i*Pdim+j)) = BVAL;

    for (i=0; i<Ndim; i++)
        for (j=0; j<Mdim; j++)
            *(C+(i*Ndim+j)) = 0.0;

    /* Do the matrix product */

    start_time = omp_get_wtime(); 
    for (i=0; i<Ndim; i++){
        for (j=0; j<Mdim; j++){
            tmp = 0.0;
            for(k=0;k<Pdim;k++){
                /* C(i,j) = sum(over k) A(i,k) * B(k,j) */
                tmp += *(A+(i*Ndim+k)) *  *(B+(k*Pdim+j));
            }
            *(C+(i*Ndim+j)) = tmp;
        }
    }
   
    run_time = omp_get_wtime() - start_time;
 
    printf(" Order %d multiplication in %f seconds \n", ORDER, run_time);
           
    /* Check the answer */
           
    cval = Pdim * AVAL * BVAL;
    errsq = 0.0;
    for (i=0; i<Ndim; i++){
        for (j=0; j<Mdim; j++){
            err = *(C+i*Ndim+j) - cval;
            errsq += err * err;
        }
    }

    if (errsq > TOL) 
        printf("\n Errors in multiplication: %f",errsq);
    else
        printf("\n Hey, it worked");

    printf("\n all done \n");
}
