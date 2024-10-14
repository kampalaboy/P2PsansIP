#ifndef Thread_h
#define Thread_h

#include "../datastructures/queue.h"
#include <pthread.h>

struct ThreadJob{
    void * (*job)(void *arg);
    void *arg;
};

struct ThreadPool{
    
    int num_threads;
    int active;
    struct Queue work;
    pthread_t *pool;
    pthread_mutex_t lock;
    pthread_cond_t signal;

    void (*add_work)(struct ThreadPool *threadpool, struct ThreadJob threadjob);
};

struct ThreadJob threadjob_constructor(void * (*job)(void *arg), void *arg);
struct ThreadPool threadpool_constructor(int num_threads);

struct ThreadPool threadpool_destructor(struct ThreadPool *threadpool);

#endif 