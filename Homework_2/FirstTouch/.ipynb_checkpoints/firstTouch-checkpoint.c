#include <omp.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#define NTHREADS 12
int main()
{
    long int VectorSize = 2e9;
    double* a = (double*)malloc(VectorSize*sizeof(double));
    double* b = (double*)malloc(VectorSize*sizeof(double));
    double* c = (double*)malloc(VectorSize*sizeof(double));
    double d = 3.543;

    omp_set_num_threads(NTHREADS);
    //Step 1.a Initialization by initial thread only 
   for (int j = 0; j < VectorSize; j++) { 
       a[j] = 1.1-j;
       b[j] = 2.2+j;
       c[j] = 3.3*j;
    }

    //Step 1.b Initialization by all threads (first touch)
    /*#pragma omp parallel for schedule(static)
    for (int j = 0; j < VectorSize; j++) { 
       a[j] = 1.1-j;
       b[j] = 2.2+j;
       c[j] = 3.3*j;
    }*/

    double start_time = omp_get_wtime();
   //Step 2 Compute
    #pragma omp parallel for schedule(static)
    for (int j = 0; j < VectorSize; j++) {
       a[j] = b[j] + d * c[j];
    }
    
     printf("Execution time: %f seconds \n", omp_get_wtime()-start_time);
     printf("OpenMP threads binding policy is %d \n", omp_get_proc_bind()); 
     // note that OpenMP Binding policy will be 3 if "close"
     // note that OpenMP Binding policy will be 4 if "spread"
     printf("Number of threads %d \n", NTHREADS); 
}