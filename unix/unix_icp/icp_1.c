#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "sys/stat.h"
#include "fcntl.h"

#define NAMEDPIPE_NAME "my_named_pipe"
#define BUFSIZE 50

int main(int argc, char **argv)
{

    int Handle, len;
    char buffer[BUFSIZE];

    if(mkfifo(NAMEDPIPE_NAME, 0777))
    {
	perror("mkfifo");
	return EXIT_FAILURE;
    }

    printf("Named pipe %s is created\n", NAMEDPIPE_NAME);

    if((Handle = open(NAMEDPIPE_NAME, O_RDONLY)) <= 0)
    {
	perror("open");
	return EXIT_FAILURE;
    }

    printf("%s is opened\n", NAMEDPIPE_NAME);

    do
    {
	memset(buffer, '\0', BUFSIZE);
	if((len = read(Handle, buffer, BUFSIZE - 1)) <= 0)
	{
	    perror("read");
	    close(Handle);
	    remove(NAMEDPIPE_NAME);
	    return EXIT_SUCCESS;
	}
	printf("Incoming message[%d]: %s\n", len, buffer);
    } while( 1 );

    return EXIT_SUCCESS;

}
