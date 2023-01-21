#include <stdio.h>
#include <omp.h>

#define N_THREADS 8

int main(){
    printf("starting\n");
    omp_set_num_threads(N_THREADS);
    int N = 10000;
    int is_cpu = 1;
    int* arr = (int*)malloc(N*N*sizeof(int));
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            arr[i*N+j] = 0;
        }
    }

    double start = omp_get_wtime();
    int T = 5;
    
    // #pragma omp parallel for
    
    #pragma omp target map(tofrom: arr[0:N*N]) map(from:is_cpu)
    {
      is_cpu = omp_is_initial_device();
      #pragma omp parallel for
      for(int i=0; i<N; i++){
          for(int j=0; j<N; j++){
              for(int t = 0; t < T; ++t){
                  arr[i*N+j] += t*i*j;
              }
          }
      }
    }
    // printf("%d\n", omp_get_num_devices());
    double end = omp_get_wtime();

    //select random point (i,j) in [0, N-1]x[0, N-1]
    int i = rand() % N;
    int j = rand() % N;
    int val = arr[i*N+j];
    int exp = 0;
    for(int t = 0; t < T; ++t){
        exp += t*i*j;
    }
    free(arr);
    printf("arr[%d, %d]=%d, exp=%d\n", i, j, val, exp);
    if(exp != val)
        printf("ERROR: wrong value\n");
    else
        printf("OK: correct value\n");
      
    printf("Running on %s\n", is_cpu ? "CPU" : "GPU");
    printf("time: %f\n", end-start);

    return 0;
}


// #include <omp.h>

// #include <iostream>

// constexpr int N = 16;
// int main() {
//   int is_cpu = true;
//   int *data = static_cast<int *>(malloc(N * sizeof(int)));

//   // Initialization
//   for (int i = 0; i < N; i++) data[i] = i;

//   // Add the target directive here, including the map clause.
// #pragma omp target map(from:is_cpu) map(tofrom:data[0:N])
//   {
//     is_cpu = omp_is_initial_device();
// #pragma omp parallel for
//     for (int i = 0; i < N; i++) {
//       data[i] *= 2;
//     }
//   }

//   // Print Output
//   std::cout << "Running on " << (is_cpu ? "CPU" : "GPU") << "\n";
//   for (int i = 0; i < N; i++) std::cout << data[i] << "\n";

//   free(data);
//   return 0;
// }