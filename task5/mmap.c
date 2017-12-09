#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int fd1, fd2, l;
	void *ptr1, *ptr2;

	if ((fd1 = open(argv[1], O_RDONLY)) < 0) {
		printf("Can't open 1st file\n");
		exit(1);
	}
	if ((fd2 = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0666)) < 0) {
		printf("Can't open 2nd file\n");
		exit(1);
	}
	l = lseek(fd1, 0, SEEK_END);
	//printf("%d\n", l);
	ftruncate(fd2, l);
	if ((ptr1 = mmap(NULL, l, PROT_READ, MAP_SHARED, fd1, 0)) == MAP_FAILED) {
		printf("mmap1 failed\n");
		exit(1);
	}
	close(fd1);
	if ((ptr2 = mmap(NULL, l, PROT_WRITE, MAP_SHARED, fd2, 0)) == MAP_FAILED) {
		printf("mmap2 failed\n");
		exit(1);
	}

	memcpy(ptr2, ptr1, l);
	munmap(ptr1, l);
	munmap(ptr2, l);
	return 0;
}

