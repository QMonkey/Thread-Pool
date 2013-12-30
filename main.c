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
	sleep(atoi(argv[3]));
	thread_pool_destroy(pool);
	printf("\n");
	return 0;
}
