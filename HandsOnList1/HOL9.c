#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<time.h>
#include<stdlib.h>
#include<sys/stat.h>

int main(void) {
	
	struct stat st;
	int fd = open("testfile.txt", O_CREAT|O_RDONLY);
	if (fd < 0) {
		perror("Failed ");
		return -1;
	}
	
	int res = fstat(fd, &st);
	if (res < 0) {
		perror("Failed to fetch stat ");
		return -1;
	}
	
	printf("Inode No. : %ju \n", st.st_ino);
	printf("Link Count : %ju \n", st.st_nlink);
	printf("UID: %ju \n", st.st_uid);
	printf("GID: %ju \n", st.st_gid);
	printf("Size: %jd bytes \n", st.st_size);
	printf("Block Size: %jd bytes \n", st.st_blksize);
	printf("No. of Blocks %jd \n", st.st_blocks);
	printf("Time of Last access: %s \n", ctime(&st.st_atime));
	printf("Time of last modification: %s \n", ctime(&st.st_mtime));
	printf("Time of last change: %s \n", ctime(&st.st_ctime));
	
	return 0;

}
