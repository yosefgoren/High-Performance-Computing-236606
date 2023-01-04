#include <omp.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void gauss_seidel(int tsteps, int size, double **p) {
   for (int t = 0; t < tsteps; ++t) {
      for (int i = 1; i < size-1; ++i) {
         for (int j = 1; j < size-1; ++j) {
                          p[i][j] = 0.2*p[i][j-1] + 
                                    0.3*p[i][j+1] +
                                    0.1*p[i-1][j] + 
                                    0.4*p[i+1][j];
         }
      }
   }
}


int main(){ 
    
  double **p;
  int size = 6002;
  int tsteps = 100;
  int i,j;
  double start;
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
   gauss_seidel(tsteps, size, p);

   printf("Serial Execution time: %f sec \n", omp_get_wtime()-start);
   
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
