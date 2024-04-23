#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 64
#define NUM_POINTS 1000000

int circle_point_cnt = 0;
pthread_mutex_t mutex;

void *calculate_pi() {
    unsigned int rand = time(NULL) + pthread_self();
    int cnt = 0;

    double x, y = 0.0;

    for (int i = 0; i < (int) (NUM_POINTS / NUM_THREADS); i++) {
        x = (double) rand_r(&rand) / RAND_MAX * 2 - 1;
        y = (double) rand_r(&rand) / RAND_MAX * 2 - 1;

        if (x * x + y * y <= 1) cnt++;
    }

    pthread_mutex_lock(&mutex);
    circle_point_cnt += cnt;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);

}

void minisystem()
{
    printf("minisystem\n");
}

int add()
{
    int a,b;
    
    printf("enter first integer...  ");
    scanf("%d", &a);

    printf("enter second integer...  ");
    scanf("%d", &b);

    return a+b;
}

double montecarlo_pi() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, calculate_pi, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    double res = (double) 4.0 * circle_point_cnt / NUM_POINTS;
    circle_point_cnt = 0;
    pthread_mutex_destroy(&mutex);

    return res;
}
