/*
 *  shwater2d.c solves the two dimensional shallow water equations 
 *  using the Lax-Friedrich's scheme
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define cell_size 3
#define xstart 0.0
#define ystart 0.0
#define xend 4.0
#define yend 4.0

#define Q(i, j, k) Q[((k) + n * ((j) + m * (i)))]


/* Check that the solution is finite */
void validate(double *Q, int m, int n) {
  static const int points_to_check[3][100] =
  {
    {61, 17, 32, 98, 67, 69, 71, 63, 18, 51, 76, 63, 62, 80, 92, 53, 32, 96, 81, 74, 66, 7, 21, 20, 5, 13, 42, 19, 69, 30, 2, 14, 90, 27, 78, 72, 50, 87, 43, 4, 31, 60, 23, 96, 10, 31, 43, 13, 66, 41, 92, 65, 87, 49, 72, 4, 69, 19, 32, 50, 2, 29, 48, 49, 3, 70, 63, 59, 80, 41, 49, 35, 9, 91, 42, 78, 33, 35, 74, 13, 89, 58, 22, 57, 54, 45, 80, 52, 49, 82, 38, 40, 23, 52, 31, 22, 63, 85, 29},
    {72, 5, 47, 35, 62, 1, 84, 43, 76, 76, 65, 38, 0, 67, 38, 24, 69, 56, 48, 65, 20, 41, 66, 96, 84, 9, 34, 50, 96, 3, 50, 16, 99, 97, 4, 43, 43, 77, 69, 48, 6, 49, 6, 5, 67, 64, 68, 60, 83, 25, 29, 76, 85, 28, 50, 79, 59, 25, 13, 83, 54, 85, 97, 74, 73, 68, 69, 41, 20, 91, 81, 16, 18, 62, 1, 13, 98, 66, 44, 5, 72, 21, 15, 74, 32, 3, 25, 70, 87, 89, 65, 94, 39, 56, 11, 74, 95, 45, 65, 7},
    {0, 2, 0, 0, 2, 2, 1, 2, 1, 0, 1, 2, 0, 0, 0, 2, 0, 2, 2, 1, 0, 1, 1, 1, 2, 2, 2, 0, 1, 2, 0, 1, 2, 2, 2, 2, 1, 1, 1, 2, 2, 1, 0, 1, 0, 2, 2, 2, 1, 1, 0, 0, 2, 1, 2, 1, 2, 0, 2, 0, 2, 0, 0, 0, 1, 0, 1, 1, 1, 0, 2, 1, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 1, 1, 2, 0, 2, 0, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2}
  };
  for(int b = 0; b < 100; b++)
    printf("%lf ", Q(points_to_check[2][b], points_to_check[0][b], points_to_check[1][b]));
  printf("\n");
  int i, j, k;
  for (i = 0; i < n; i++) 
    for (j = 0; j < m; j++) 
      for (k = 0; k < cell_size;  k++)
    if (!isfinite(Q(k, j, i))) {
      fprintf(stderr, "Invalid solution of serial solver\n");
      exit(-1);
    }
}

/* Flux function in the x-direction */
void fx(double *Q, double **fq, int m, int n, int j) {  
  int i;
  const double g = 9.81;

  for (i = 0; i < m; i++) {
    fq[0][i] = Q(1, i, j);
    fq[1][i] = (pow(Q(1, i, j), 2) / Q(0, i, j))  + 
      (g * pow(Q(0, i, j), 2)) / 2.0;
    fq[2][i] = (Q(1, i, j) * Q(2, i, j)) / Q(0, i, j);
  }
  
}

/* Flux function in the y-direction */
void fy(double *Q, double **fq, int m, int n, int i) {
  int j;
  const double g= 9.81;

  for (j = 0; j < n; j++) {
    fq[0][j] = Q(2, i, j);
    fq[1][j] = (Q(1, i, j) * Q(2, i, j)) / Q(0, i, j);    
    fq[2][j] = (pow(Q(2, i, j), 2) / Q(0, i, j))  + 
      (g * pow(Q(0, i, j), 2)) / 2.0;
  }
}


/*
  This is the Lax-Friedrich's scheme for updating volumes
*/
void laxf_scheme_2d(double *Q, double **ffx, double **ffy, double **nFx, double **nFy,
            int m, int n, double dx, double dy, double dt) {
  int i, j, k;
    
  /* Calculate and update fluxes in the x-direction */
  for (i = 1; i < n; i++) {
    fx(Q, ffx, m, n, i);
    for (j = 1; j < m; j++) 
      for (k = 0; k < cell_size;  k++) 
    nFx[k][j] = 0.5 * ((ffx[k][j-1] + ffx[k][j]) -
           dx/dt * (Q(k, j, i) - Q(k, j-1, i)));
    for (j = 1; j < m-1; j++)
      for (k = 0; k < cell_size;  k++) 
    Q(k, j, i) = Q(k, j, i)  - dt/dx * ((nFx[k][j+1] - nFx[k][j]));
      
  }

  /* Calculate and update fluxes in the y-direction */
  for (i = 1; i < m; i++) {
    fy(Q, ffy, m, n, i);
    for (j = 1; j < n; j++)
      for (k = 0; k < cell_size; k++)
    nFy[k][j] = 0.5 * ((ffy[k][j-1] + ffy[k][j]) - 
           dy/dt * (Q(k, i, j) - Q(k, i, j -1)));
    for (j = 1; j <  n-1; j++) 
      for (k = 0; k < cell_size; k++)
    Q(k,i,j) = Q(k,i,j) -  dt/dy * ((nFy[k][j+1]  -  nFy[k][j]));
  }

}


void solver(double *Q, double **ffx, double **ffy, double **nFx, double **nFy,
        int m, int n, double tend, double dx, double dy, double dt) {
  double bc_mask[3] = {1.0, -1.0, -1.0};
  double time;
  int i, j, k, steps;
  
  steps = ceil(tend / dt);  
  for (i = 0, time = 0.0; i < steps; i++, time += dt) { 

    /* Apply boundary condition */
    for (j = 1; j < n - 1 ; j++) {
      for (k = 0; k < cell_size; k++) {
    Q(k, 0, j) = bc_mask[k] *  Q(k, 1, j);
    Q(k, m-1, j) = bc_mask[k] *  Q(k, m-2, j);
      }
    }

    for (j = 0; j < m; j++)  {
      for (k = 0; k < cell_size; k++) {
    Q(k, j, 0) = bc_mask[k] * Q(k, j, 1);
    Q(k, j, n-1) = bc_mask[k] * Q(k, j, n-2);
      }
    }
     
    /* Update all volumes with the Lax-Friedrich's scheme */     
    laxf_scheme_2d(Q, ffx, ffy, nFx, nFy, m, n, dx, dy, dt);  
  
  }
}
  
/*
  This is the main routine of the program, which allocates memory 
  and setup all parameters for the problem.
  
  You don't need to parallelize anything here!
  
  However, it might be useful to change the m and n parameters 
  during debugging
*/
int main(int argc, char **argv) {
  srand(42);//make deterministic  
  int i, j, m, n;
  double *Q;
  double *x, *y;
  double **ffx, **nFx, **ffy, **nFy;
  double dx, dt, epsi, delta, dy, tend, tmp, stime, etime;

  /* Use m volumes in the x-direction and n volumes in the y-direction */    
  m = 1000;
  n = 1000;
  
  /*
    epsi      Parameter used for initial condition
    delta     Parameter used for initial condition
    dx        Distance between two volumes (x-direction)
    dy        Distance between two volumes (y-direction)
    dt        Time step
    tend      End time
  */
  epsi = 2.0;
  delta = 0.5;
  dx = (xend - xstart) / (double) m;
  dy = (yend - ystart) / (double) n;
  dt = dx / sqrt( 9.81 * 5.0);
  tend = 0.1;
  
  /* Add two ghost volumes at each side of the domain */
  m = m + 2;
  n = n + 2;

  /* Allocate memory for the domain */
  Q = (double *) malloc(m * n * cell_size *  sizeof(double));

  x = (double *) malloc(m * sizeof(double));
  y = (double *) malloc(n * sizeof(double));	

  /* Allocate memory for fluxes */
  ffx = (double **) malloc(cell_size * sizeof(double *));
  ffy = (double **) malloc(cell_size * sizeof(double *));
  nFx = (double **) malloc(cell_size * sizeof(double *));
  nFy = (double **) malloc(cell_size * sizeof(double *));

  ffx[0] = (double *) malloc(cell_size * m * sizeof(double));
  ffy[0] = (double *) malloc(cell_size * n * sizeof(double));
  nFx[0] = (double *) malloc(cell_size * m * sizeof(double));
  nFy[0] = (double *) malloc(cell_size * n * sizeof(double));

  for (i = 0; i < cell_size; i++) {
    ffx[i] =  ffx[0] + i * m;
    nFx[i] =  nFx[0] + i * m;
    ffy[i] =  ffy[0] + i * n;
    nFy[i] =  nFy[0] + i * n;
  }
    
  for (i = 0,tmp= -dx/2 + xstart; i < m; i++, tmp += dx)
    x[i] = tmp;

  for (i = 0,tmp= -dy/2 + ystart; i < n; i++, tmp += dy)
    y[i] = tmp;

  /* Set initial Gauss hump */
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      Q(0, i, j) = 4.0;
      Q(1, i, j) = 0.0;
      Q(2, i, j) = 0.0;
    }
  }

  for (i = 1; i < m-1; i++) {
    for (j = 1; j < n-1; j++) {
      Q(0, i, j) = 4.0 + epsi * exp(-(pow(x[i] - xend / 4.0, 2) + pow(y[j] - yend / 4.0, 2)) /
                  (pow(delta, 2)));
    }
  }

  stime = omp_get_wtime();
  solver(Q, ffx, ffy, nFx, nFy, m, n, tend, dx, dy, dt);
  etime = omp_get_wtime();

  printf("validating...\n");
  validate(Q, m,  n);

  printf("Serial Solver took %g seconds\n", etime - stime);



  free(Q);
  free(x);
  free(y);

  free(ffx[0]);
  free(ffy[0]);
  free(nFx[0]);
  free(nFy[0]);

  free(ffx);
  free(ffy);
  free(nFx);
  free(nFy);

  return 0;    
}