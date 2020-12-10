#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO_NAME "FIFO_FD"
int main(void) {
	char buf[100];
	int num, fd;
	/* making a FD for FIFO */
	if(mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
		perror("mknod error");
	}

	/* We are waiting for a reader */
	/* We open the FD, when the reader opens the FD */
	printf("Writer: waiting for a reader.\n");
	fd = open(FIFO_NAME, O_WRONLY);
	printf("Writer: the reader ready.\n");
	printf("Writer: your input: ");

	/* send the user input data to the reader via FIFO */
	while (fgets(buf, sizeof(buf), stdin), !feof(stdin)) {
		if ((num = write(fd, buf, strlen(buf))) == -1){
			perror("write error");
		}
		else{
		printf("Writer: wrote %d bytes\n", num);
		}
	}
	close(fd);


	return 0;
}
