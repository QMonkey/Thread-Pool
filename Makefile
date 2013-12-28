PROG = thread_pool
OBJS = main.o task_queue.o thread_pool.o
CC = gcc

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $@ -lpthread

%.o: %.c
	$(CC) -c $<

clean:
	-rm -rf $(OBJS) $(PROG)
