#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/mman.h"

#define SHARED_MEMORY_OBJECT_NAME "my_shared_memory"
#define SHARED_MEMORY_OBJECT_SIZE 50
#define SHM_CREATE 1
#define SHM_PRINT 3
#define SHM_CLOSE 4


void usage(const char *str)
{
	printf("Usage: %s <create|write|read|unlink> ['text']\n", str);
}


int main(int argc, char **argv)
{

	int shm, len, cmd, mode;
	char *addr;

	mode = 0;

	if(argc < 2)
	{
		usage(argv[0]);
		return EXIT_FAILURE;
	}

	if((!strcmp(argv[1], "create") || !strcmp(argv[1], "write")) && (argc == 3))
	{
		len = strlen(argv[2]);
		len = (len <= SHARED_MEMORY_OBJECT_SIZE) ? len : SHARED_MEMORY_OBJECT_SIZE;
		mode = O_CREAT;
		cmd = SHM_CREATE;
	}
	else
	{
		if(!strcmp(argv[1], "print"))
		{
			cmd = SHM_PRINT;
		}
		else
		{
			if(!strcmp(argv[1], "unlink"))
			{
				cmd = SHM_CLOSE;
			}
			else
			{
				usage(argv[0]);
				return EXIT_FAILURE;
			}
		}
	}

	if((shm = shm_open(SHARED_MEMORY_OBJECT_NAME, mode | O_RDWR, 0777)) == -1)
	{
		perror("shm_open");
		return EXIT_FAILURE;
	}

	if(cmd == SHM_CREATE)
	{
		if(ftruncate(shm, SHARED_MEMORY_OBJECT_SIZE + 1) == -1)
		{
			perror("ftruncate");
			return EXIT_FAILURE;
		}
	}

	addr = mmap(0, SHARED_MEMORY_OBJECT_SIZE + 1, PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);

	if(addr == (char *)-1)
	{
		perror("mmap");
		return EXIT_FAILURE;
	}

	switch(cmd)
	{
		case SHM_CREATE:
			memcpy(addr, argv[2], len);
			addr[len] = '\0';
			printf("Shared memory filled in. You may run '%s print' to see value.\n", argv[0]);
			break;
		case SHM_PRINT:
			printf("Got from shared memory: %s\n", addr);
			break;
	}

	munmap(addr, SHARED_MEMORY_OBJECT_SIZE);
	close(shm);

	if(cmd == SHM_CLOSE)
	{
		shm_unlink(SHARED_MEMORY_OBJECT_NAME);
	}

	return EXIT_SUCCESS;

}
