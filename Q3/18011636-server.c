#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO_NAME "FIFO_FD"
int main(){
	char buf[100];
	char to_client[200];
	int num, fd, add;

	/* making a FD, which is the same one the writer uses, for FIFO */
	if(mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
		perror("mknod error");
	}

	/* We are waiting for the writer */
	/* We open the FD, when the writer opens the FD */
	fd = open(FIFO_NAME, O_RDONLY);

	/* Receive the data sent from the writer via FIFO */
	do {
		if ((num = read(fd, buf, 100)) == -1){
			perror("read error");
		}
		else {
			buf[num] = '\0';
			add=atoi(buf);
			printf("Read\n %d",add);
			add+=add;
			
		}
	} while (num > 0);

	return 0;
}
