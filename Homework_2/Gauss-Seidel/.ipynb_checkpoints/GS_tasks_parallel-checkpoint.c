
void gauss_seidel(int tsteps, int size, double **p) {
      for (int t = 0; t < tsteps; ++t) {
         for (int i = 1; i < size-1; ++i) {
            for (int j = 1; j < size-1; ++j) {   
               //create a different task for each update
               p[i][j] = 0.25 * (p[i][j-1] + // left
                                 p[i][j+1] + // right
                                 p[i-1][j] + // top
                                 p[i+1][j]); // bottom
            }
         }
      }
   }
}
