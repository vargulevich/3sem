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

	struct mymsgbuf {
		long mtype;
		char mtext[32];
	};
	struct mymsgbuf mybuf;

	int fd = open("text2.txt", O_WRONLY | O_CREAT, 0666);
	for(i = 0; i < 3; i++) {
	key = ftok(pathname, 0);
	msqid = msgget(key, 0666 | IPC_CREAT);

	mybuf.mtype = 1;
	msgrcv(msqid, &mybuf, 32, mybuf.mtype, 0);
	printf("%s\n", mybuf.mtext);
	write(fd, mybuf.mtext, 9);
	}
	close(fd);
	return 0;
}
