#include <stdio.h>
#include <omp.h>

int x = 0;

void foo(){
    printf("aaa\n");
    for(int i = 0; i < 1; ++i){
        #pragma omp for
        for(int i = 0; i < 1; ++i){
            x++;
            printf("%d\n", omp_get_thread_num());
        }
        // #pragma omp for
        // for(int i = 0; i < 10; ++i){
        //     x++;
        //     // printf("%d\n", omp_get_thread_num());
        // }
        // #pragma omp for
        // for(int i = 0; i < 10; ++i){
        //     x++;
        //     // printf("%d\n", omp_get_thread_num());
        // }
        // #pragma omp for
        // for(int i = 0; i < 10; ++i){
        //     x++;
        //     // printf("%d\n", omp_get_thread_num());
        // }
    }
}

int main(){
    double stime = omp_get_wtime();
    #pragma omp parallel
    {
        foo();
    }
    
    // for(int i = 0; i < 100000; ++i){
    //     #pragma omp parallel for
    //     for(int i = 0; i < 10; ++i){
    //         x++;
    //         //printf("%d\n", omp_get_thread_num());
    //     }
    //     #pragma omp parallel for
    //     for(int i = 0; i < 10; ++i){
    //         x++;
    //         // printf("%d\n", omp_get_thread_num());
    //     }
    //     #pragma omp parallel for
    //     for(int i = 0; i < 10; ++i){
    //         x++;
    //         // printf("%d\n", omp_get_thread_num());
    //     }
    //     #pragma omp parallel for
    //     for(int i = 0; i < 10; ++i){
    //         x++;
    //         // printf("%d\n", omp_get_thread_num());
    //     }
    // }

    printf("time: %lf, %d\n", omp_get_wtime()-stime, x);
}