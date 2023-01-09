#include <omp.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define NTHREADS 12

#define DEBUG 0

void gauss_seidel(int tsteps, int size, int TS, double **p) {
  int t, ii, jj;
  #if DEBUG
  printf("{\n");
  #endif
  #pragma omp parallel
  {
    #pragma omp single
    for(t=0; t< tsteps; ++t){
      #if DEBUG
      printf("\t{'T', %d},\n", t);
      #endif
      for(ii = 1; ii+TS < size; ii+=TS){
        for(jj = 1; jj+TS < size; jj+=TS){
          #if DEBUG
          for (int i = ii; i < ii+TS; ++i){
            for (int j = jj; j < jj+TS; ++j){
              printf("\t{'A', %d, %d},\n", i, j);
            }
          }
          #endif
          //insert all the following work (on TSxTS cells) to a single task
          //Only the bottom right item in each block is used as the in/out variable for the purposes of task dependency.
          #pragma omp task firstprivate(ii, jj) depend(in: p[ii+TS-1][jj-1], p[ii-1][jj+TS-1]) depend(out: p[ii+TS-1][jj+TS-1])
          for (int i = ii; i < ii+TS; ++i){
            for (int j = jj; j < jj+TS; ++j){
              #if DEBUG
              printf("\t{'S', %d, %d},\n", i, j);
              #endif
              p[i][j] = 0.2*p[i][j-1]+ 
                        0.3*p[i][j+1]+
                        0.1*p[i-1][j]+ 
                        0.4*p[i+1][j];       
            }
          }
        }
      }
      #pragma omp taskwait
    }
  }
  #if DEBUG
  printf("}\n");
  #endif
}


int main(){ 
    
  double **p;
  int size = 6002;
  int tsteps = 100;
  int i,j;
  double start;
  int TS = 100;
  omp_set_num_threads(NTHREADS);
  p=(double **)malloc(sizeof(double *)*size);  
  
  for(i=0;i<size;i++){
    p[i]=(double *)malloc(sizeof(double)*size); 
   }
 

  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      p[i][j]=(0.05*i+0.04*j);
    }
  }
     
   start = omp_get_wtime();
   gauss_seidel(tsteps, size, TS, p);

   printf("Tasks Blocks Execution time: %f sec, with %d threads \n", omp_get_wtime()-start, NTHREADS);
   
   double sum=0;
   for(i=0;i<size;i++){
     for(j=0;j<size;j++){
        sum += p[i][j];
     }
   }
   
    printf("sum = %f \n", sum); 
   if(fabs(sum - 9825298683.981915) < 0.0001)
       printf("correct answer\n");
    else
       printf("ERROR = wrong answer\n");
   
    
   //free memory
   for(i=0;i<size;i++){
     free(p[i]);
   }
   free(p);
   return 0;
}
