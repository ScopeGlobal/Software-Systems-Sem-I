#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main() {

	int softL = symlink("tempfile.txt", "tempfileHL");
	if (softL < 0) {
		perror("Soft Link Creation failed ");
		return 1;
	}
	
	int hardL = link("tempfile.txt", "tempfileSL");
	if (hardL < 0) {
		perror("Hard Link Creation failed ");
		return 1;
	}
	
	int mkfifo = mknod("newfifopipe", S_IFIFO, 1);
	if (mkfifo < 0 ) {
		perror("FIFO Pipe Creation failed ");
		return 1;
	}
	
	return 0;
}
