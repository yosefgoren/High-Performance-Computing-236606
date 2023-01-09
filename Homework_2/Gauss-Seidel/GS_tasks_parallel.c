
//'TS_DUMMY' was added so this will be compatible with the block-based impl for experimintation.
void gauss_seidel(int tsteps, int size, int TS_DUMMY, double **p) {
   int t, i, j;
   printf("{\n");
   #pragma omp parallel
   {
      #pragma omp single
      for (t = 0; t < tsteps; ++t) {
         printf("\t{'T', %d},\n", t);
         for (i = 1; i < size-1; ++i) {
            for (j = 1; j < size-1; ++j) {
               //create a different task for each update
               printf("\t{'A', %d, %d},\n", i, j);
               #pragma omp task firstprivate(i, j) depend(in: p[i][j-1], p[i-1][j]) depend(out: p[i][j])
               {
                  printf("\t{'S', %d, %d},\n", i, j);
                  p[i][j] =
                     0.2*p[i][j-1]+
                     0.3*p[i][j+1]+
                     0.1*p[i-1][j]+ 
                     0.4*p[i+1][j];
               }
            }
         }
         #pragma omp taskwait
      }
   }
   printf("}\n");
}
