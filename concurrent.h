#ifndef CONCURRENT_H
#define CONCURRENT_H

#include <semaphore.h>
#include <pthread.h>
#include <stdint.h>

typedef struct task_queue_node_t
{
	void* (*callback)(void*);
	void *arg;
	struct task_queue_node_t *next;
} task_queue_node_t;

typedef struct
{
	sem_t semaphore;
	pthread_mutex_t mutex;
	pthread_t *tids;
	task_queue_node_t *head;
	uint32_t size;
	int flag;
} thread_pool_t;

#endif
