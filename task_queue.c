#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "concurrent.h"
#include "task_queue.h"

task_queue_node_t* task_queue_node_create(void* (*callback)(void*),void *arg)
{
	task_queue_node_t *node = (task_queue_node_t*)malloc(sizeof(task_queue_node_t));
	node->callback = callback;
	node->arg = arg;
	node->next = NULL;
	return node;
}

task_queue_node_t* task_queue_take(thread_pool_t *pool)
{
	sem_wait(&pool->semaphore);
	pthread_mutex_lock(&pool->mutex);
	task_queue_node_t *node = task_queue_pop(&pool->head);
	pthread_mutex_unlock(&pool->mutex);
	return node;
}

void task_queue_put(thread_pool_t *pool,void* (*callback)(void*),void *arg)
{
	pthread_mutex_lock(&pool->mutex);
	task_queue_push(&pool->head,callback,arg);
	pthread_mutex_unlock(&pool->mutex);
	sem_post(&pool->semaphore);
}

void task_queue_push(task_queue_node_t **head_ptr,void* (*callback)(void*),void *arg)
{
	if(*head_ptr != NULL)
	{
		task_queue_push(&(*head_ptr)->next,callback,arg);
	}
	else
	{
		task_queue_node_t *node = task_queue_node_create(callback,arg);
		*head_ptr = node;
	}
}

task_queue_node_t* task_queue_pop(task_queue_node_t **head_ptr)
{
	task_queue_node_t *tmp = *head_ptr;
	*head_ptr = tmp->next;
	tmp->next = NULL;
	return tmp;
}

void task_queue_delete(task_queue_node_t *node)
{
	free(node);
}

void task_queue_destroy(task_queue_node_t **head_ptr)
{
	if(*head_ptr != NULL)
	{
		task_queue_destroy(&(*head_ptr)->next);
		task_queue_delete(*head_ptr);
	}
}
