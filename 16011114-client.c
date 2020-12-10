#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO_NAME "16011114_FD"

int main(void) {
	char buf[100];
	int data = 0;
	int num, fd;

	// create FIFO for FD
	if(mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
		perror("mknod error");
	}

	// Wait for writer
	printf("Reader: waiting for a writer.\n");
	fd = open(FIFO_NAME, O_RDONLY);		// open file with READ ONLY mode
	printf("Reader: the writer ready.\n");
	
	// Read data from FD
	do {
		if ((num = read(fd, buf, strlen(buf))) == -1) {	// read file
			perror("read error");
		}
		else {
			data = atoi(buf[0]);
			printf("%d+1 = %d\n", data, data+1);
		}
	} while (num > 0);
	
	return 0;
}

