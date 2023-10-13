#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

struct Admin {
	int userid;
	char username[80];
	char email[80];
	char password[80];
};

int main(void) {
    int fd = open("admin.txt", O_RDWR);
    struct Admin admin;
    admin.userid = 1;
    strcpy(admin.username, "admin");
    strcpy(admin.email, "admin@admin.com");
    strcpy(admin.password, "admin");

    int write_stat = write(fd, &admin, sizeof(admin));
    if (write_stat < 0) {
        perror("Write Failed");
        return -1;
    }

    close(fd);
    return 0;
}