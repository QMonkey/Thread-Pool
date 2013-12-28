#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include "concurrent.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern task_queue_node_t* task_queue_node_create(void* (*callback)(void*),void *arg);
extern task_queue_node_t* task_queue_take(thread_pool_t *pool);
extern void task_queue_put(thread_pool_t *pool,void* (*callback)(void*),void *arg);
extern void task_queue_push(task_queue_node_t **head_ptr,
		void* (*callback)(void*),void *arg);
extern task_queue_node_t* task_queue_pop(task_queue_node_t **head_ptr);
extern void task_queue_delete(task_queue_node_t *node);
extern void task_queue_destroy(task_queue_node_t **head_ptr);

#ifdef __cplusplus
}
#endif

#endif
