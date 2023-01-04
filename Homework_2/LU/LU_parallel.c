#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>
#include "omp.h"

void printMatrix(double *a,int n);//helper to print matrix


void *memset(void *str,int c, size_t t);//too many warnings...so you know.
void *memcpy(void *str1,const void *str2,size_t n);

int main(int argc, char **argv)
{
  int i,j,k,t;
  int n;
  int flag;
  double l1,u1;
  double *a;
  double *b;
  double *c;
  double start;
  double end;

  n=2000;
  // n=500;
 
  a=(double *)malloc(sizeof(double)*n*n);  
  b=(double *)malloc(sizeof(double)*n*n);
  c=(double *)malloc(sizeof(double)*n*n);

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      a[i*n+j]=((rand()%10)+1);
    }
  }
  memcpy((void *)b,(const void *)a,(size_t)(n*n*sizeof(double)));  
  start = omp_get_wtime();

  /*Perform LU decomposition*/
  for(k=0;k<n;k++)
  {
    #pragma omp parallel for
    for(j=k+1;j<n;j++)
    {
      a[k*n+j]=a[k*n+j]/a[k*n+k];//Scaling
    }
    #pragma omp parallel for private(j)
    for(i=k+1;i<n;i++)
    { 
      for(j=k+1;j<n;j++)
      {
        a[i*n+j]=a[i*n+j]-a[i*n+k]*a[k*n+j];
      } 
    }
  }
  /*end of LU decomposition*/

 printf("Operation took %lf\n",omp_get_wtime()-start);

 /*Inplace Verification step */
//  #pragma omp parallel for private(i,j,k,l1,u1) collapse(2)
 for(i=0;i<n;i++){
   for(j=0;j<n;j++){
     c[i*n+j]=0;

     for(k=0;k<n;k++){
       if(i>=k)l1=a[i*n+k];
       else l1=0;

       if(k==j)u1=1;
       else if(k<j)u1=a[k*n+j]; 
       else u1=0.0;
       
        c[i*n+j]=c[i*n+j]+(l1*u1);
      
     } 
   }
  }
 flag=0;
 for(i=0;i<n;i++){
   for(j=0;j<n;j++){
     if(fabs(c[i*n+j]-b[i*n+j])>0.01){
         flag=1;
         break;
     }
    }
 }
 
 if(flag==1){
     printf("Error : Not a match\n");
 }
 else printf("Match\n");
 
 /*Time to free the memory*/
  free(a);
  free(b);
  free(c);

  return 0;
}


void printMatrix(double *mat,int n){
  int i,j;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      printf("%lf ",mat[i*n+j]);
    }
    printf("\n");
  }
  printf("------------------------------------------------\n");
}