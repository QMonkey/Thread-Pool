#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <stdint.h>
#include <semaphore.h>
#include <pthread.h>

#include "concurrent.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern thread_pool_t* thread_pool_create(uint32_t size);
extern void thread_pool_start(thread_pool_t *pool);
extern void thread_pool_execute(thread_pool_t *pool,
		void* (*callback)(void*),void *arg);
extern void thread_pool_stop(thread_pool_t *pool);
extern void thread_pool_destroy(thread_pool_t *pool);

#ifdef __cplusplus
}
#endif

#endif
