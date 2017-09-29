/*
  Write a program which allow you to: 
- run another programs via command line.
- get exit codes of terminated programs

## TIPS:
1. Use "2_fork_wait_exit.c" and "4_exec_dir.c" from examples. Combine them.
2. Parse input string according to the type of exec* (see "man exec").
   a) if execvp is used, string splitting into "path" and "args" is all you need.
3. Collect exit codes via waitpid/WEXITSTATUS.
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

int main() {
	pid_t pid;
   	int status;
   	char a[3][1000];
   	char line[1000];
   	while(1) {
   		printf("Write Name and Args through a Space!\n");
   		int i = 0, k = 2, j = 0;
	   	fgets(line, 1000, stdin);
	   	int len = strlen(line);
	 	
	 	a[0][0] = '.';
	 	a[0][1] = '/';
		for (; i < len; ++i) {
			if (line[i] == ' ') {
				a[j][k] = '\0';
				j++;
				k = 0;
			} else {
				a[j][k++] = line[i];
			}
		} 
		if (j == 0) {
			a[j][k-1] = '\0';
		}
		if (j == 1) {
			a[j][k-1] = '\0';
		} 
		len = strlen(a[0]);
		k = 0;
		for(i = 2; i < len; ++i) {
			a[2][k++] = a[0][i];
		}
		a[2][k] = '\0';
	   	switch(pid = fork()) {
	   		case -1:
	   			printf("fork error\n");
	   		case 0:
	   			if (j == 1) {
					if (execlp(a[0],a[2],a[1],NULL) == -1) {
						printf("NO SUCH PROGRAM OR DIRECTORY\n");
	   						status = 1;
	   						exit(1);
					} // this is the code the child runs 
	   			} else {
	   				if (j == 0) {
	 
	   					if (execlp(a[0],a[2],NULL) == -1) {
	   						printf("NO SUCH PROGRAM OR DIRECTORY\n");
	   						status = 1;
	   						exit(1);
	   					}
	   				} else {
	   					printf("R U OK?\nINCORRECT DATA\n");
	   					status = 1;
	   					exit(1);
	   				}
	   			}
	   		default:

				waitpid(pid, &status, 0); // this is the code the parent runs
				printf("Ret code: %d\n", WEXITSTATUS(status));
	   	}
	}

	return 0;
}
