#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "thread_pool.h"

static int value = 0;
static int counter = 0;

static void* callback(void *arg)
{
	int *ptr = (int*)arg;
	printf("%d ",*ptr);
	*ptr = ++counter;
	return NULL;
}

static void* callback_function(void *arg)
{
	printf("Before sleep:\t%d\n",(int)arg);
	sleep(5);
	printf("After sleep:\t%d\n",(int)arg);
	return NULL;
}

int main(int argc,char **argv)
{
	if(argc < 4)
	{
		fprintf(stderr,"No enough parameter.\n");
		exit(EXIT_FAILURE);
	}
	thread_pool_t *pool = thread_pool_create(atoi(argv[1]));
	thread_pool_start(pool);
	int i;
	int end = atoi(argv[2]);
	for(i = 0; i < end; ++i)
	{
		thread_pool_execute(pool,callback,&value);
	}
	printf("\n");
	sleep(5);
	for(i = 0; i < end; ++i)
	{
		thread_pool_execute(pool,callback_function,(void*)i);
	}
	sleep(atoi(argv[3]));
	thread_pool_destroy(pool);
	printf("\n");
	return 0;
}
