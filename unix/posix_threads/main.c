#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "pthread.h"

#define NUM_THREADS 4

void * my_thread_function(void *args)
{
	int id;
	time_t start_time, end_time;

	start_time = time(NULL);
	id = *((int *)args);
	printf("Hello from my_thread_function with id = %d[started at %s]\n", id, ctime(&start_time));
	end_time = time(NULL);
	printf("Goodbye from my_thread_function with id = %d[ended at %s]\n", id, ctime(&end_time));
	pthread_exit(NULL);
}

int main(void)
{
	int i, tmp, counter;
	int args[NUM_THREADS];
	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;

	for(counter = 1; counter <= NUM_THREADS; counter++)
		args[counter - 1] = counter;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

	for(i = 0; i < NUM_THREADS; i++)
	{
		tmp = pthread_create(&threads[i], &attr, my_thread_function, (void *)&args[i]);

		if(tmp != 0)
		{
			printf("Creating thread #%d failed!\n", i + 1);
			return EXIT_FAILURE;
		}
	}

	for(i = 0; i < NUM_THREADS; i++)
	{
		tmp = pthread_join(threads[i], NULL);

		if(tmp != 0)
		{
			printf("Joing thread #%d failed!\n", i + 1);
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;

}


