#include <stdio.h>

#pragma omp declare simd notinbranch
double f(double x){
  double ret;
  ret = 4.0 / (x*x + 1.0);
  return  ret; 
}
