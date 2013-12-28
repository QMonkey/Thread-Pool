#include <semaphore.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "task_queue.h"
#include "thread_pool.h"

static void* thread_pool_run(void *arg);

thread_pool_t* thread_pool_create(uint32_t size)
{
	thread_pool_t *pool = (thread_pool_t*)malloc(sizeof(thread_pool_t));
	sem_init(&pool->semaphore,0,0);
	pthread_mutex_init(&pool->mutex,NULL);
	pool->tids = (pthread_t*)malloc(sizeof(pthread_t) * size);
	pool->head = NULL;
	pool->flag = 0;
	pool->size = size;
	return pool;
}

void* thread_pool_run(void *arg)
{
	thread_pool_t *pool = (thread_pool_t*)arg;
	while(pool->flag)
	{
		task_queue_node_t *node = task_queue_take(pool);
		node->callback(node->arg);
		task_queue_delete(node);
	}
}

void thread_pool_start(thread_pool_t *pool)
{
	if(!pool->flag)
	{
		pool->flag = 1;
		uint32_t i;
		for(i = 0; i < pool->size; ++i)
		{
			pthread_create(pool->tids + i,NULL,thread_pool_run,pool);
		}
	}
}

void thread_pool_execute(thread_pool_t *pool,void* (*callback)(void*),void *arg)
{
	task_queue_put(pool,callback,arg);
}

void thread_pool_stop(thread_pool_t *pool)
{
	pool->flag = 0;
}

void thread_pool_destroy(thread_pool_t *pool)
{
	thread_pool_stop(pool);
	sem_destroy(&pool->semaphore);
	pthread_mutex_destroy(&pool->mutex);
	task_queue_destroy(&pool->head);
	free(pool->tids);
	free(pool);
}
