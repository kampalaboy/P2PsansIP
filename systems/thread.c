#include "thread.h"

void * threadjob(void *arg);
void add_work(struct ThreadPool *threadpool, struct ThreadJob threadjob);

struct ThreadPool threadpool_constructor(int num_threads){

    struct ThreadPool threadpool;
    threadpool.num_threads = num_threads;
    threadpool.active = 1;
    threadpool.work = queue_constructor();
    threadpool.lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    threadpool.signal = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

    pthread_mutex_lock(&threadpool.lock);
    threadpool.pool = malloc(sizeof(pthread_t[num_threads]));

    for (int i=0; i<num_threads; i++){
        pthread_create(&threadpool.pool[i], NULL, threadjob ,&threadpool);
    }

    pthread_mutex_unlock(&threadpool.lock);
    threadpool.add_work = add_work;
    return threadpool;
}

struct ThreadJob threadjob_constructor(void * (*job)(void *arg), void *arg){
    
    struct ThreadJob threadjob;
    threadjob.job = job;
    threadjob.arg = arg;
    return threadjob;
}

void threadpool_destructor(struct ThreadPool *threadpool){

    threadpool->active = 0;
    for (int i=0; i<threadpool->num_threads; i++){
        pthread_cond_signal(&threadpool->signal);
    }
    for (int i=0; i<threadpool->num_threads; i++){
        pthread_join(threadpool->pool[i], NULL);
    }
    
    free(threadpool->pool);
    queue_destructor(&threadpool->work);
}

void * threadjob(void *arg){

    struct ThreadPool *threadpool = (struct ThreadPool *)arg;
    while(threadpool->active==1){

        pthread_mutex_lock(&threadpool->lock);
        pthread_cond_wait(&threadpool->signal, &threadpool->lock);

        struct ThreadJob threadjob = *(struct ThreadJob *)threadpool->work.peek(&threadpool->work);
        threadpool->work.pop(&threadpool->work);
        pthread_mutex_unlock(&threadpool->lock);
        
        if (threadjob.job){

            threadjob.job(threadjob.arg);
        }
    }
    return NULL;
}

void add_work(struct ThreadPool *threadpool, struct ThreadJob threadjob)
{
    pthread_mutex_lock(&threadpool->lock);
    threadpool->work.push(&threadpool->work, &threadjob, sizeof(threadjob));
    pthread_cond_signal(&threadpool->signal);
    pthread_mutex_unlock(&threadpool->lock);
}