#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

struct Student {
	int stud_id;
	char stud_name[80];
	int num_courses;
	int courses[80];
	char password[80];
	char email[80];
	int activity_stat;
};

struct Faculty {
	int fac_id;
	char fac_name[80];
	char email[80];
	char password[80];
	int num_courses;
	int courses[80];
};

int add_student(struct Student student) {

	int fd = open("student.txt", O_RDWR);
	if (fd < 0) {
		perror("Opening Failed");
		return -1;
	}
	int end_file = 0;
	while (1) {
		struct Student temp;
		int read_stat = read(fd, &temp, sizeof(temp));
		if (read_stat == 0) {
			break;
		} else if (temp.stud_id == student.stud_id) {
			return -1;
		}
	}
	
	int write_stat = write(fd, &student, sizeof(student));
	if (write_stat < 0) {
		return -1;
	} else {
		return 1;
	}
	
}

int add_faculty(struct Faculty faculty) {

	int fd = open("faculty.txt", O_RDWR);
	if (fd < 0) {
		perror("Opening Failed");
		return -1;
	}
	int end_file = 0;
	while (1) {
		struct Faculty temp;
		int read_stat = read(fd, &temp, sizeof(temp));
		if (read_stat == 0) {
			break;
		} else if (temp.fac_id == faculty.fac_id) {
			return -1;
		}
	}
	
	int write_stat = write(fd, &faculty, sizeof(faculty));
	if (write_stat < 0) {
		return -1;
	} else {
		return 1;
	}

}

int act_deact(int activate_id) {

	int fd = open("student.txt", O_RDWR);
	if (fd < 0) {
		perror("Opening Failed");
		return -1;
	}
	int end_file = 0;
	int act_deact_stat;
	while (1) {
		struct Student temp;
		int read_stat = read(fd, &temp, sizeof(temp));
		if (read_stat == 0) {
			return -1;
		} else if (temp.stud_id == activate_id) {
			if (temp.activity_stat == 0) {
				temp.activity_stat = 1;
				act_deact_stat = 1;
			} else {
				temp.activity_stat = 0;
				act_deact_stat = 0;
			}
			lseek(fd, -1 * (sizeof(temp)), SEEK_CUR);
			int write_stat = write(fd, &temp, sizeof(temp));
			if (write_stat < 0) {
				perror("Writing Failed");
				return -1;
			}
			break;
		}
	}	
	
	return act_deact_stat;

}

int stud_update(char *updated, int stud_update_choice, int student_id) {

	int fd = open("student.txt", O_RDWR);
	if (fd < 0) {
		perror("Opening Failed");
		return -1;
	}
	while (1) {
		struct Student temp;
		int read_stat = read(fd, &temp, sizeof(temp));
		if (read_stat == 0) {
			return -1;
		} else if (temp.stud_id == student_id) {
			if (stud_update_choice == 1) {
				strcpy(temp.stud_name, updated);
			} else {
				strcpy(temp.email, updated);
			}
			lseek(fd, -1 * (sizeof(temp)), SEEK_CUR);
			int write_stat = write(fd, &temp, sizeof(temp));
			if (write_stat < 0) {
				perror("Writing Failed");
				return -1;
			}
			break;
		}
	}	
	
	return 1;

}

int fac_update(char *updated, int fac_update_choice, int fac_id) {

	int fd = open("faculty.txt", O_RDWR);
	if (fd < 0) {
		perror("Opening Failed");
		return -1;
	}
	while (1) {
		struct Faculty temp;
		int read_stat = read(fd, &temp, sizeof(temp));
		if (read_stat == 0) {
			return -1;
		} else if (temp.fac_id == fac_id) {
			if (fac_update_choice == 1) {
				strcpy(temp.fac_name, updated);
			} else {
				strcpy(temp.email, updated);
			}
			lseek(fd, -1 * (sizeof(temp)), SEEK_CUR);
			int write_stat = write(fd, &temp, sizeof(temp));
			if (write_stat < 0) {
				perror("Writing Failed");
				return -1;
			}
			break;
		}
	}	
	
	return 1;

}

int main(void) {

	int server, client;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len = sizeof(client_addr);
	char buf[1024];
	
	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server < 0) {
		perror("Server side Socket creation failed");
		return -1;
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5002);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	int bind_stat = bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (bind_stat < 0) {
		perror("Binding Failed");
		return -1;
	}
	
	int listen_stat = listen(server, 5);
	if (listen_stat < 0) {
		perror("Listen Failed");
		return -1;
	}
	
	printf("The server is now listening on port 5002 \n");
	
	client = accept(server, (struct sockaddr *)&client_addr, &client_len);
	if (client < 0) {
		perror("Client Acceptance Failed");
		return -1;
	}

	char choice[3];
	int rec_stat = recv(client, choice, sizeof(choice), 0);
	if (rec_stat < 0) {
		perror("Receiving Failed");
		return -1;
	}
	char role;
	if (choice[0] == '3') {
		role = 's';
	} else if (choice[0] == '4') {
		role = 'f';
	} else if (choice[0] == '5') {
		role = 'a';
	} else {
		role = 'x';
	}

	int send_stat = send(client, &role, sizeof(role), 0);
	if (send_stat < 0) {
		perror("Sending Failed");
		return -1;
	}
	
	switch (role) {
		case 'a':
			printf("Someone logged in as an Admin \n");
			while (1) {
				int admin_choice;
				rec_stat = recv(client, &admin_choice, sizeof(admin_choice), 0);
				if (rec_stat < 0) {
					perror("Receiving Failed");
					return -1;
				}	
				
				if (admin_choice == 1) {
					struct Student student;
					rec_stat = recv(client, &student, sizeof(student), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					printf("Student ID %d \n", student.stud_id);
					printf("Student Name %s \n", student.stud_name);
					printf("Student Email %s \n", student.email);
					
					int add_stat = add_student(student);
					
					send_stat = send(client, &add_stat, sizeof(add_stat), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
				} else if (admin_choice == 2) {
					struct Faculty faculty;
					rec_stat = recv(client, &faculty, sizeof(faculty), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					printf("Faculty ID %d \n", faculty.fac_id);
					printf("Faculty Name %s \n", faculty.fac_name);
					printf("Faculty Email %s \n", faculty.email);
					
					int add_stat = add_faculty(faculty);

					send_stat = send(client, &add_stat, sizeof(add_stat), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					
				} else if (admin_choice == 3) {
					int activate_id;
					rec_stat = recv(client, &activate_id, sizeof(activate_id), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					printf("Student ID to be Activated/Deactivated- %d \n", activate_id);
					
					int act_stat = act_deact(activate_id);

					send_stat = send(client, &act_stat, sizeof(act_stat), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}					
				} else if (admin_choice == 4) {
					int student_id;
					rec_stat = recv(client, &student_id, sizeof(student_id), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					int stud_update_choice;
					rec_stat = recv(client, &stud_update_choice, sizeof(stud_update_choice), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					char updated[80];
					if (stud_update_choice == 1) {
						rec_stat = recv(client, updated, sizeof(updated), 0);
						if (rec_stat < 0) {
							perror("Receiving Failed");
							return -1;
						}
						printf("Updated Name %s", updated);	
					} else if (stud_update_choice == 2) {
						rec_stat = recv(client, updated, sizeof(updated), 0);
						if (rec_stat < 0) {
							perror("Receiving Failed");
							return -1;
						}				
						printf("Updated Email %s", updated);
					} else {
						continue;
					}
					
					int stud_upd_stat = stud_update(updated, stud_update_choice, student_id);
					send_stat = send(client, &stud_upd_stat, sizeof(stud_upd_stat), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}					
					
				} else if (admin_choice == 5) {
					int fac_id;
					rec_stat = recv(client, &fac_id, sizeof(fac_id), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					int fac_update_choice;
					rec_stat = recv(client, &fac_update_choice, sizeof(fac_update_choice), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					char updated_fac[80];
					if (fac_update_choice == 1) {
						rec_stat = recv(client, updated_fac, sizeof(updated_fac), 0);
						if (rec_stat < 0) {
							perror("Receiving Failed");
							return -1;
						}
						printf("Updated Name %s", updated_fac);	
					} else if (fac_update_choice == 2) {
						rec_stat = recv(client, updated_fac, sizeof(updated_fac), 0);
						if (rec_stat < 0) {
							perror("Receiving Failed");
							return -1;
						}				
						printf("Updated Email %s", updated_fac);
					} else {
						continue;
					}
					
					int fac_upd_stat = fac_update(updated_fac, fac_update_choice, fac_id);
					send_stat = send(client, &fac_upd_stat, sizeof(fac_upd_stat), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}					
									
				} else {
					break;
				}
			}
			break;
		
		case 'f':
			printf("Someone logged in as a Faculty \n");
			while (1) {
				int fac_choice;
				rec_stat = recv(client, &fac_choice, sizeof(fac_choice), 0);
				if (rec_stat < 0) {
					perror("Receiving Failed");
					return -1;
				}
				
				if (fac_choice == 1) {
					struct {
						int course_id;
						char course_name[80];
						int enroll_count;
						int enrolled[150];
					} course;
					rec_stat = recv(client, &course, sizeof(course), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					printf("Course ID- %d \n", course.course_id);
					printf("Course Name- %s \n", course.course_name);

					int cadd_stat = 1;
					send_stat = send(client, &cadd_stat, sizeof(cadd_stat), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
						
				} else if (fac_choice == 2) {
					int del_id;
					rec_stat = recv(client, &del_id, sizeof(del_id), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					int cdel_stat = 1;
					send_stat = send(client, &cdel_stat, sizeof(cdel_stat), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
				} else if (fac_choice == 3) {
					int co_id;
					rec_stat = recv(client, &co_id, sizeof(co_id), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}					
					
					int enrollees[150];
					enrollees[0] = 4;
					for (int i = 1; i < 150; i++) {
						enrollees[i] = -1;
					}
					
					send_stat = send(client, enrollees, sizeof(enrollees), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
				} else if (fac_choice == 4) {
					char new_pass[80];
					rec_stat = recv(client, new_pass, sizeof(new_pass), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}				
					
					int pass_stat = 1;
					send_stat = send(client, &pass_stat, sizeof(pass_stat), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}				
				} else {
					break;
				}
			}
			break;
		
		case 's':
			printf("Someone logged in as a Student \n");
			while (1) {
				int stud_choice;
				rec_stat = recv(client, &stud_choice, sizeof(stud_choice), 0);
				if (rec_stat < 0) {
					perror("Receiving Failed");
					return -1;
				}			
				
				if (stud_choice == 1) {
					int cid;
					rec_stat = recv(client, &cid, sizeof(cid), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int creg_stat = 1;
					send_stat = send(client, &creg_stat, sizeof(creg_stat), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
				} else if (stud_choice == 2) {
					int unen_id;
					rec_stat = recv(client, &unen_id, sizeof(unen_id), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int cunen_stat = 1;
					send_stat = send(client, &cunen_stat, sizeof(cunen_stat), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
				} else if (stud_choice == 3) {
					int enrolled_c[150];
					enrolled_c[0] = 4;
					for (int i = 1; i < 150; i++) {
						enrolled_c[i] = -1;
					}

					send_stat = send(client, enrolled_c, sizeof(enrolled_c), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}				
					
				} else if (stud_choice == 4) {
					char s_new_pass[80];
					rec_stat = recv(client, s_new_pass, sizeof(s_new_pass), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}				
					
					int s_pass_stat = 1;
					send_stat = send(client, &s_pass_stat, sizeof(s_pass_stat), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}	
				} else {
					break;
				}
			}
			break;
		
		default:
			printf("Auth Failed \n");
			break;		
	}
	
	close(server);
	close(client);
	return 0;
	
}
