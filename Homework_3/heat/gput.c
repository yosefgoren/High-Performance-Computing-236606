#include <stdio.h>
#include <omp.h>

#define N_THREADS 8

int main(){
    printf("starting\n");
    omp_set_num_threads(N_THREADS);
    int N = 10000;
    int* arr = (int*)malloc(N*N*sizeof(int));
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            arr[i*N+j] = 0;
        }
    }

    
    double start = omp_get_wtime();
    int T = 100;
    
    // #pragma omp parallel for
    #pragma omp target map(tofrom: arr[0:N*N]) device(0)
    for(int i=0; i<N; i++){
        if(i == 0)
            printf("is initial: %d.\n", omp_is_initial_device());
        for(int j=0; j<N; j++){
            for(int t = 0; t < T; ++t){
                arr[i*N+j] += t*i*j;
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
    printf("time: %f\n", end-start);

    return 0;
}