#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEFAULT_ITERATIONS 100000

int counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int num_threads = 2;
int iterations = DEFAULT_ITERATIONS;

// TAMBAHAN: barrier dan struct timing
pthread_barrier_t barrier;
typedef struct {
    int id;
    double exec_time;
} ThreadData;

void* worker(void* arg) {
    ThreadData* data = (ThreadData*)arg; // TAMBAHAN

    pthread_barrier_wait(&barrier);      // TAMBAHAN: barrier

    // TAMBAHAN: catat waktu mulai
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < iterations; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }

    // TAMBAHAN: catat waktu selesai
    clock_gettime(CLOCK_MONOTONIC, &end);
    data->exec_time = (end.tv_sec - start.tv_sec) +
                      (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Thread %d: %.4f detik\n", data->id, data->exec_time);

    return NULL;
}

int main(int argc, char* argv[]) {

    // 1. Validasi argumen baris perintah
    if(argc >= 2) {
        char* endptr;
        long val = strtol(argv[1], &endptr, 10);
        if(*endptr != '\0' || val < 1 || val > 100) {
            fprintf(stderr, "Error: masukkan integer antara 1-100\n");
            return 1;
        }
        num_threads = (int)val;
    }
    printf("Jumlah thread: %d\n\n", num_threads);

    // 2. Inisialisasi barrier
    pthread_barrier_init(&barrier, NULL, num_threads);

    // 3. Pengukuran waktu eksekusi per thread
    pthread_t* threads = malloc(num_threads * sizeof(pthread_t));
    ThreadData* data   = malloc(num_threads * sizeof(ThreadData));
    if (!threads || !data) {
        perror("malloc failed");
        return 1;
    }

    for (int i = 0; i < num_threads; i++) {
        data[i].id = i + 1;
        data[i].exec_time = 0;
        if (pthread_create(&threads[i], NULL, worker, &data[i]) != 0) {
            perror("pthread_create failed");
            for (int j = 0; j < i; j++) {
                pthread_cancel(threads[j]);
            }
            free(threads);
            free(data);
            return 1;
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Rata-rata waktu
    double total = 0;
    for(int i = 0; i < num_threads; i++)
        total += data[i].exec_time;
    printf("Rata-rata: %.4f detik\n", total / num_threads);

    printf("\nFinal counter: %d\n", counter);
    printf("Expected: %d\n", num_threads * iterations);

    // 4. Penanganan sumber daya
    pthread_mutex_destroy(&lock);
    pthread_barrier_destroy(&barrier); // TAMBAHAN
    free(threads);
    free(data);                        // TAMBAHAN
    printf("Resource berhasil dibersihkan.\n");

    return 0;
}