/*
Write a duplex pipe implementation.
typedef struct {
  int txd[2]; 
  int rxd[2]; 
} dpipe_t;
1) This pipe should connect some process with his child, for continuous communication.
2) Be careful with opened descriptors.
3) When one process is terminated, the other should also exit.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

struct dpipe_t{
	int txd[2];
	int rxd[2];
};

int main() {
	struct dpipe_t fd;
	size_t size;
	int status;
	char buf1[4096], buf2[4096];
	char str1[4096], str2[4069];

	printf("Dad want to tell to his kid: \n");
	fgets(str1, 4095, stdin);
	printf("Kid want to tell to his dad: \n");
	fgets(str2, 4095, stdin);

	if (pipe(fd.txd) == -1) {
               perror("pipe");
               printf("PIPE txd FAILED\n");
               exit(-1);
           }

    if (pipe(fd.rxd) == -1) {
    	perror("pipe");
    	printf("PIPE rxd FAILED\n");
    	exit(-1);
    } 

    pid_t pid = fork();
	if (pid == -1) {
		printf("FORK FAILED\n");
		exit(-1);  
	}

	if (pid > 0) {		//parent
		size = write(fd.txd[1], str1, strlen(str1));
		if (size == -1) {
			printf("WRITE FAILED\n");
			exit(-1);
		}
		close(fd.txd[1]);

		waitpid(pid, &status, 0);

		size = read(fd.rxd[0], buf1, strlen(str2));
		if (size == -1) {
			printf("READ FAILED\n");
			exit(-1);
		}
		printf("I'm a Dad! My kid says: %s\n", buf1);
		close(fd.rxd[0]);
	}

	if (pid == 0) {		//kid
		size = read(fd.txd[0], buf2, strlen(str1));
		if (size == -1) {
			printf("READ FAILED\n");
			exit(-1);
		}
		printf("I'm a kid. My dad says : %s\n", buf2);
		close(fd.txd[0]);

		size = write(fd.rxd[1], str2, strlen(str2));
		if (size == -1) {
			printf("WRITE FAILED\n");
			exit(-1);
		}
		close(fd.rxd[1]);
	}

	return 0;
}

