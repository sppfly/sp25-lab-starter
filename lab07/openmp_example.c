#include <stdio.h>
#include <omp.h>

int main() {

        #pragma omp for
            for (int i = 0; i < 10; i++) {
                int tid = omp_get_thread_num();
                printf("%d thread\n", tid);
            }


    printf("main thread\n");
}
