#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO_NAME "16011114_FD"

int main(void) {
	char buf[100];
	int data;
	int num, fd;

	// Create FD for FIFO
	if(mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
		perror("mknod error");
	}

	// Wait for reader
	printf("Writer: waiting for a reader.\n");
	fd = open(FIFO_NAME, O_WRONLY);
	printf("Writer: the reader ready.\n");
	printf("Writer: your input: ");

	// Send data to FD
	while (fgets(buf, sizeof(buf), stdin), !feof(stdin)) {
		if ((num = write(fd, buf, strlen(buf))) == -1)	// write file
			perror("write error");
		else
			printf("Writer: wrote %d bytes\n", num);
	}

	return 0;
}

