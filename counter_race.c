#include <stdio.h>
#include <pthread.h>

#define ITERATIONS 100000

int counter = 0;

void* worker(void* arg) {
    for(int i = 0; i < ITERATIONS; i++) {
        counter++;
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("FINAL = %d\n", counter);

    return 0;
}