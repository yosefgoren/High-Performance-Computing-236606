#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define NUM_THREADS 24
#define SOFTENING 1e-9f

#define N_BODIES 20000
#define N_DIMS 3

typedef struct { float x, y, z, vx, vy, vz; } Body;

typedef struct { float positions[N_BODIES][N_DIMS], velocities[N_BODIES][N_DIMS]; } Bodies;

void randomizeBodies_old(float *data, int n) {
  for (int i = 0; i < n; i++) {
    data[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
  }
}

void randomizeBodies(Bodies* data) {
  int bytes = N_BODIES*sizeof(Body);
  float *buf = (float*)malloc(bytes);
  Body *p = (Body*)buf;
  randomizeBodies_old(buf, 6*N_BODIES);
  for(int i = 0; i < N_BODIES; ++i){
    data->positions[i][0] = p[i].x;
    data->positions[i][1] = p[i].y;
    data->positions[i][2] = p[i].z;
    data->velocities[i][0] = p[i].vx;
    data->velocities[i][1] = p[i].vy;
    data->velocities[i][2] = p[i].vz;
  }
  free(buf);
}

void update_loading_icon(char* c, int iter){
  switch(iter%8){
    case 0: *c = '-'; break;
    case 1: *c = '\\'; break;
    case 2: *c = '|'; break;
    case 3: *c = '/'; break;
    case 4: *c = '-'; break;
    case 5: *c = '\\'; break;
    case 6: *c = '|'; break;
    case 7: *c = '/'; break;
  }
}


int main(const int argc, const char** argv) {
  
  srand(42);//make deterministic.

  const float dt = 0.01f; // time step
  const int nIters = 10;  // simulation iterations
  
  omp_set_num_threads(NUM_THREADS);
  Bodies *p = (Bodies*)malloc(sizeof(Bodies));

  randomizeBodies(p);
  
  double totalTime = 0.0;
  double start_time = omp_get_wtime();
  for (int iter = 1; iter <= nIters; iter++) {
    char c;
    // update_loading_icon(&c, iter);
    // printf("%c Crunching Numbers...\r", c);

    #pragma omp parallel for schedule(guided)
    for(int effected = 0; effected < N_BODIES; ++effected){
      float force[N_DIMS] = {0.0f, 0.0f, 0.0f};
      
      for(int j = 0; j < N_BODIES; ++j){
        float delta[N_DIMS];
        float* pos_a = p->positions[j], *pos_b = p->positions[effected];
        delta[0] = pos_a[0] - pos_b[0];
        delta[1] = pos_a[1] - pos_b[1];
        delta[2] = pos_a[2] - pos_b[2];
        float distSqr = delta[0]*delta[0]+delta[1]*delta[1]+delta[2]*delta[2] + SOFTENING;
        float invDist = 1.0f / sqrtf(distSqr);
        float invDist3 = invDist * invDist * invDist;
        force[0] += delta[0] * invDist3;
        force[1] += delta[1] * invDist3;
        force[2] += delta[2] * invDist3;
      }
      float* vs = p->velocities[effected];
      vs[0] += dt*force[0];
      vs[1] += dt*force[1];
      vs[2] += dt*force[2];
    }
    #pragma omp parallel for schedule(guided)
    for(int effected = 0; effected < N_BODIES; ++effected){
      float* pos = p->positions[effected];
      float* vel = p->velocities[effected];
      pos[0] += vel[0] * dt;
      pos[1] += vel[1] * dt;
      pos[2] += vel[2] * dt;
    }
  }
  printf("Parallel Execution time: %f seconds with %d threads\n\n", omp_get_wtime()-start_time, NUM_THREADS);

  float res[3];
  for(int dim = 0; dim < N_DIMS; ++dim){
    res[dim] = p->positions[0][dim];
  }
  free(p);

  const float ref[3] = {-127.683983, 218.130157, -121.554520};
  printf("Expecting to hardcoded: %f %f %f\n", ref[0], ref[1], ref[2]);
  printf("Got: %f %f %f\n", res[0], res[1], res[2]);
  int success = (fabs(res[0]-ref[0])<0.01f) && (fabs(res[1]-ref[1])<0.01f) && (fabs(res[2]-ref[2])<0.01f);
  printf("Test %s\n", (success) ? "PASSED" : "FAILED");
}