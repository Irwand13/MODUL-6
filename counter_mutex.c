#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define DEFAULT_ITERATIONS 100000

int counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int num_threads = 2;    
int iterations = DEFAULT_ITERATIONS;

void* worker(void* arg) {

    for(int i = 0; i < iterations; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t*threads = malloc(num_threads * sizeof(pthread_t));
    if (!threads) {
        perror("malloc failed");
        return 1;
    }
     
    for (int i = 0; i < num_threads; i++) {
        if (pthread_create(&threads[i], NULL, worker, NULL) != 0) {
            perror("Failed to create thread");
            for (int j = 0; j < i; j++) {
                pthread_join(threads[j], NULL);
            }
            free(threads);
            return 1;
        }
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("FINAL COUNTER = %d\n", counter);
    printf("EXPECTED = %d\n", num_threads * iterations);
    pthread_mutex_destroy(&lock);
    free(threads);

    return 0;
}