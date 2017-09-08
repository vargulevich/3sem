/* draft for daemon writing. Close the filestreams to go further ..." */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	pid_t pid = 0;
	pid=fork();
	int status;
	if (pid < 0) {
		printf("fork() error\n");
		return -1;
	} else if (pid != 0) {
		waitpid(pid, &status, 0);
		exit(EXIT_SUCCESS);
	}

	if (setsid()==-1) {
		printf("setsid() error\n");
		return -1;
	}
	/* do something in new session */
	printf("pid=%d:sid=%d\n", getpid(),getsid(getpid()));
		
	return 0;
}
