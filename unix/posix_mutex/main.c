#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "pthread.h"

#define NUM_OF_THREADS 10

static FILE * FileHandler;
pthread_mutex_t mutex;

void * my_thread_function(void *args)
{
	int id;
	time_t start_time, end_time;

	id = *((int *)args);
	start_time = time(NULL);

	printf("Thread[id: %d] started at %s", id, ctime(&start_time));

	pthread_mutex_lock(&mutex);
		fprintf(FileHandler, "Thread[id: %d] started at %s", id, ctime(&start_time));
	pthread_mutex_unlock(&mutex);

	end_time = time(NULL);
	printf("Thread[id: %d] ended at %s", id, ctime(&end_time));
	pthread_mutex_lock(&mutex);
		fprintf(FileHandler, "Thread[id: %d] ended at %s", id, ctime(&end_time));
	pthread_mutex_unlock(&mutex);

	return NULL;
}

int main(void)
{
	pthread_t threads[NUM_OF_THREADS];
	int args[NUM_OF_THREADS];
	int i, tmp;
	char *OutputFileName = "out.txt";
	time_t StartTime;

	StartTime = time(NULL);
	FileHandler = fopen(OutputFileName, "a+");

	if(FileHandler == NULL)
	{
		printf("Can not open file %s\n", OutputFileName);
		return EXIT_FAILURE;
	}

	fprintf(FileHandler, "\nLog:%s", ctime(&StartTime));

	for(i = 0; i < NUM_OF_THREADS; i++)
	{
		args[i] = i + 1;
	}

	printf("Num of threads = %d\n", NUM_OF_THREADS);
	printf("Output file name is %s\n", OutputFileName);
	printf("Start time is %s\n", ctime(&StartTime));

	pthread_mutex_init(&mutex, NULL);

	for(i = 0; i < NUM_OF_THREADS; i++)
	{
		tmp = pthread_create(&threads[i], NULL, my_thread_function, (void *)(&args[i]));

		if(tmp != 0)
		{
			printf("Creating thread #%d failure!\n", i + 1);
			return EXIT_FAILURE;
		}

	}

	for(i = 0; i < NUM_OF_THREADS; i++)
	{
		tmp = pthread_join(threads[i], NULL);

		if(tmp != 0)
		{
			printf("Joining thread #%d failure!\n", i + 1);
			return EXIT_FAILURE;
		}

	}

	pthread_mutex_destroy(&mutex);

	if(FileHandler != NULL)
		fclose(FileHandler);

	return EXIT_SUCCESS;
}

