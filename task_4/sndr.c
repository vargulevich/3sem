#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 

int main() {
	int msqid;
	char pathname[] = "msgq.c";
	key_t key;
	int i, len;
	char text[32];
	//fgets(text, 32, stdin);


	struct mymsgbuf {
		long mtype;
		char mtext[32];
	};
	struct mymsgbuf mybuf;
	int fd = open("text.txt", O_RDONLY | O_CREAT);

	for(i = 0; i < 3; i++) {
	read(fd, text, 9);
	printf("%s\n", text);
	key = ftok(pathname, 0);
	msqid = msgget(key, 0666 | IPC_CREAT);

	mybuf.mtype = 1;
	strcpy(mybuf.mtext, text);
	msgsnd(msqid, &mybuf, 32,0);
	}
	close(fd);
	return 0;
}
