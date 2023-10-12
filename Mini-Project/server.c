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

struct Admin {
	int userid;
	char username[80];
	char email[80];
	char password[80];
};

struct Course {
	int course_id;
	char course_name[80];
	int intake;
	int enroll_count;
	int enrolled[150];
	int course_status;
};

struct LoginToken {
	int choice;
	int userid;
	char password[80];
};

char login(struct LoginToken login_token) {
	
	if (login_token.choice == 3) {
		int fd = open("student.txt", O_RDWR);
		if (fd < 0) {
			perror("Opening Failed");
			return 'x';
		}
		
		while(1) {
			struct Student temp;
			int read_stat = read(fd, &temp, sizeof(temp));
			if (read_stat == 0) {
				return 'x';
			}
			if (temp.stud_id == login_token.userid && strcmp(temp.password, login_token.password) == 0) {
				return 's';
			}
		}
	} else if (login_token.choice == 4) {
		int fd2 = open("faculty.txt", O_RDWR);
		if (fd2 < 0) {
			perror("Opening Failed");
			return 'x';
		}
		
		while(1) {
			struct Faculty temp;
			int read_stat = read(fd2, &temp, sizeof(temp));
			if (read_stat == 0) {
				return 'x';
			}
			if (temp.fac_id == login_token.userid && strcmp(temp.password, login_token.password) == 0) {
				return 'f';
			}
		}
	} else if (login_token.choice == 5) {
		int fd3 = open("admin.txt", O_RDWR);
		if (fd3 < 0) {
			perror("Opening Failed");
			return 'x';
		}
		
		while (1) {
			struct Admin temp;
			int read_stat = read(fd3, &temp, sizeof(temp));
			if (read_stat == 0) {
				return 'x';
			}
			if (temp.userid == login_token.userid && strcmp(temp.password, login_token.password) == 0) {
				return 'a';
			}
		}
	} else {
		return 'x';
	}
	
}

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

int add_course(int fac_id, struct Course course) {

	int fd = open("course.txt", O_RDWR);
	if (fd < 0) {
		perror("Opening Failed");
		return -1;
	}
	int end_file = 0;
	while (1) {
		struct Course temp;
		int read_stat = read(fd, &temp, sizeof(temp));
		if (read_stat == 0) {
			break;
		} else if (temp.course_id == course.course_id) {
			return -1;
		}
	}
	
	int write_stat = write(fd, &course, sizeof(course));
	if (write_stat < 0) {
		return -1;
	} 

	int fd2 = open("faculty.txt", O_RDWR);
	if (fd2 < 0) {
		perror("Opening Failed");
		return -1;
	}

	while (1) {
		struct Faculty faculty;
		int read_stat = read(fd2, &faculty, sizeof(faculty));
		if (read_stat == 0) {
			return -1;
		} else if (faculty.fac_id == fac_id) {
			faculty.courses[faculty.num_courses] = course.course_id;
			faculty.num_courses++;

			lseek(fd2, -1 * sizeof(faculty), SEEK_CUR);
			int write_stat = write(fd2, &faculty, sizeof(faculty));
			if (write_stat < 0) {
				perror("Writing Failed");
			}
			break;
		}
	}

	return 1;
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

int enroll_for_course(int student_id, int course_id) {

	int fd2 = open("course.txt", O_RDWR);
	if (fd2 < 0) {
		perror("Opening Failed");
		return -1;
	}

	while (1) {
		struct Course temp;
		int read_stat = read(fd2, &temp, sizeof(temp));
		if (read_stat == 0) {
			return -1;
		} else if (temp.course_id == course_id) {
			if (temp.enroll_count == temp.intake) {
				return 2;
			}
			temp.enrolled[temp.enroll_count] = student_id;
			temp.enroll_count++;
			lseek(fd2, -1 * sizeof(temp), SEEK_CUR);
			int write_stat = write(fd2, &temp, sizeof(temp));
			if (write_stat < 0) {
				perror("Writing Failed");
				return -1;
			}
		}
	}

	close(fd2);

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
			temp.courses[temp.num_courses] = course_id;
			temp.num_courses++;
			lseek(fd, -1 * (sizeof(temp)), SEEK_CUR);
						
			int write_stat = write(fd, &temp, sizeof(temp));
			if (write_stat < 0) {
				perror("Writing Failed");
				return -1;
			}
			break;
		}
	}

	close(fd);
	return 1;

}

int unenroll_from_course(int student_id, int course_id) {

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
			for (int i = 0; i < temp.num_courses; i++) {
				if (temp.courses[i] == course_id) {
					int tempo = temp.courses[i];
					temp.courses[i] = temp.courses[temp.num_courses - 1];
					temp.courses[temp.num_courses - 1] = tempo;
					temp.courses[temp.num_courses - 1] = -1;
					temp.num_courses--;
					break;
				}
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

	int fd2 = open("course.txt", O_RDWR);
	if (fd2 < 0) {
		perror("Opening Failed");
		return -1;
	}

	while (1) {
		struct Course temp;
		int read_stat = read(fd, &temp, sizeof(temp));
		if (read_stat == 0) {
			return -1;
		} else if (temp.course_id == course_id) {
			for (int i = 0; i < temp.enroll_count; i++)
			{
				if (temp.enrolled[i] == student_id) {
					int tempo = temp.enrolled[i];
					temp.enrolled[i] = temp.enrolled[temp.enroll_count - 1];
					temp.enrolled[temp.enroll_count - 1] = tempo;
					temp.enrolled[temp.enroll_count - 1] = -1;
					temp.enroll_count--;
					break;
				}
			}
			lseek(fd2, -1 * sizeof(temp), SEEK_CUR);
			int write_stat = write(fd2, &temp, sizeof(temp));
			if (write_stat < 0) {
				perror("Writing Failed");
				return -1;
			}
			break;
		}
	}
	return 1;
}

void unenroll_from_course_helper(int student_id, int course_id) {
	
	int fd = open("student.txt", O_RDWR);
	if (fd < 0) {
		perror("Opening Failed");
		return;
	}
	while (1) {
		struct Student temp;
		int read_stat = read(fd, &temp, sizeof(temp));
		if (read_stat == 0) {
			return;
		} else if (temp.stud_id == student_id) {
			for (int i = 0; i < temp.num_courses; i++) {
				if (temp.courses[i] == course_id) {
					int tempo = temp.courses[i];
					temp.courses[i] = temp.courses[temp.num_courses - 1];
					temp.courses[temp.num_courses - 1] = tempo;
					temp.courses[temp.num_courses - 1] = -1;
					temp.num_courses--;
					break;
				}
			}
			lseek(fd, -1 * (sizeof(temp)), SEEK_CUR);
						
			int write_stat = write(fd, &temp, sizeof(temp));
			if (write_stat < 0) {
				perror("Writing Failed");
				return;
			}
			break;
		}
	}	
	
	return;
	
}

int unlist_course(int fac_id, int course_id) {
	
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
			for (int i = 0; i < temp.num_courses; i++) {
				if (temp.courses[i] == course_id) {
					int tempo = temp.courses[i];
					temp.courses[i] = temp.courses[temp.num_courses - 1];
					temp.courses[temp.num_courses - 1] = tempo;
					temp.courses[temp.num_courses - 1] = -1;
					temp.num_courses--;
					break;
				}
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



void increment_fac_courses(int fac_id) {
	
	int fd = open("faculty.txt", O_RDWR);
	if (fd < 0) {
		perror("Opening Failed");
		return;
	}
	while (1) {
		struct Faculty temp;
		int read_stat = read(fd, &temp, sizeof(temp));
		if (read_stat == 0) {
			return;
		} else if (temp.fac_id == fac_id) {
			temp.num_courses++;
			lseek(fd, -1 * (sizeof(temp)), SEEK_CUR);
						
			int write_stat = write(fd, &temp, sizeof(temp));
			if (write_stat < 0) {
				perror("Writing Failed");
				return;
			}
			break;
		}
	}	
	
	return;
}

int del_course(int course_id) {
	
	int fd = open("course.txt", O_RDWR);
	if (fd < 0) {
		perror("Opening Failed");
		return -1;
	}	
	
	while(1) {
		struct Course temp;
		int read_stat = read(fd, &temp, sizeof(temp));
		if (read_stat == 0) {
			return -1;
		} else if (temp.course_id == course_id) {
			temp.course_status = 0;
			for(int j = 0; j < temp.enroll_count; j++) {
				unenroll_from_course_helper(temp.enrolled[j], course_id);
				temp.enrolled[j] = -1;
			}
			
			temp.enroll_count = 0;
			
			lseek(fd, -1 * (sizeof(temp)), SEEK_CUR);
			
			int write_stat = write(fd, &temp, sizeof(temp));
			if (write_stat < 0) {
				perror("Writing Failed");
				return -1;
			}
			break;
		}
	}
	
	close(fd);
	
	int fd2 = open("faculty.txt", O_RDWR);
	if (fd2 < 0) {
		perror("Opening Failed");
		return -1;
	}
	
	while(1) {
		struct Faculty fac;
		int read_stat = read(fd, &fac, sizeof(fac));
		if (read_stat == 0) {
			return -1;
		} else {
			for(int i = 0; i < fac.num_courses; i++) {
				if (fac.courses[i] == course_id) {
					int tempo = fac.courses[i];
					fac.courses[i] = fac.courses[fac.num_courses - 1];
					fac.courses[fac.num_courses - 1] = tempo;
					fac.courses[fac.num_courses - 1] = -1;
					fac.num_courses--;
					
					lseek(fd, -1 * (sizeof(fac)), SEEK_CUR);
					
					int write_stat = write(fd, &fac, sizeof(fac));
					if (write_stat < 0) {
						perror("Writing Failed");
						return -1;
					}
					break;
				}
			}
			
			
		}
	}
	
	return 1;
}

int update_course_name(int course_id, char* new_name) {
	int fd = open("course.txt", O_RDWR);
	if (fd < 0) {
		perror("Opening Failed");
		return -1;
	}

	while (1) {
		struct Course course;
		int read_stat = read(fd, &course, sizeof(course));
		if (read_stat == 0) {
			return -1;
		} else if (course.course_id == course_id) {
			strcpy(course.course_name, new_name);
		}

		lseek(fd, -1 * (sizeof(course)), SEEK_CUR);
		int write_stat = write(fd, &course, sizeof(course));
		if (write_stat < 0) {
			perror("Writing Failed");
			return -1;
		}
		break;
	}

	return 0;
}

int update_course_intake(int course_id, int new_intake) {
	int fd = open("course.txt", O_RDWR);
	if (fd < 0) {
		perror("Opening Failed");
		return -1;
	}

	while (1) {
		struct Course course;
		int read_stat = read(fd, &course, sizeof(course));
		if (read_stat == 0) {
			return -1;
		} else if (course.course_id == course_id) {
			int old_enrolled = course.enroll_count;
			int intake_delta = old_enrolled - new_intake;
			course.intake = new_intake;
			if (intake_delta > 0) {
				for (int i = new_intake; i < old_enrolled; i++)
				{
					unenroll_from_course_helper(course.enrolled[i], course_id);
					printf("Student %d unenrolled!", course.enrolled[i]);
					course.enrolled[i] = -1;
				}
				course.enroll_count = new_intake;
			}
			lseek(fd, -1 * sizeof(course), SEEK_CUR);
			int write_stat = write(fd, &course, sizeof(course));
			if (write_stat < 0) {
				perror("Writing Failed");
				return -1;
			}		
			break;
		}

	}

	return 1;
}

int change_fac_password(int fac_id, char* new_pass) {
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
			
		}
		if (temp.fac_id == fac_id) {
			strcpy(temp.password, new_pass);
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

int change_stud_password(int stud_id, char* new_pass) {

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
			
		}
		if (temp.stud_id == stud_id) {
			strcpy(temp.password, new_pass);
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

	struct LoginToken login_token;
	int rec_stat = recv(client, &login_token, sizeof(login_token), 0);
	if (rec_stat < 0) {
		perror("Receiving Failed");
		return -1;
	}
	
	
	char role = login(login_token);

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
					struct Course course;
					rec_stat = recv(client, &course, sizeof(course), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					printf("Course ID- %d \n", course.course_id);
					printf("Course Name- %s \n", course.course_name);

					int cadd_stat = add_course(login_token.userid, course);
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
					
					int cdel_stat = del_course(del_id);
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
					
					int fd = open("course.txt", O_RDWR);
					if (fd < 0) {
						perror("Opening Failed");
						return -1;
					}
					int enrollees[150];
					for (int i = 0; i < 150; i++) {
						enrollees[i] = -1;
					}
					while (1) {
						struct Course temp;
						int read_stat = read(fd, &temp, sizeof(temp));
						if (read_stat == 0) {
							break;
						} else if (temp.course_id == co_id) {
							for (int k = 0; k < 150; k++) {
								enrollees[k] = temp.enrolled[k];
							}
							break;
						}
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
					
					int pass_stat = change_fac_password(login_token.userid, new_pass);
					send_stat = send(client, &pass_stat, sizeof(pass_stat), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}				
				} else if (fac_choice == 5) {
					int course_id;
					rec_stat = recv(client, &course_id, sizeof(course_id), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					int course_update_choice;
					rec_stat = recv(client, &course_update_choice, sizeof(course_update_choice), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					int update_stat;
					if (course_update_choice == 1) {
						char updated_name[80];
						rec_stat = recv(client, updated_name, sizeof(updated_name), 0);
						if (rec_stat < 0) {
							perror("Receiving Failed");
							return -1;
						}
						update_stat = update_course_name(course_id, updated_name);
						printf("Updated Name %s", updated_name);	
					} else if (course_update_choice == 2) {
						int updated_intake;
						rec_stat = recv(client, &updated_intake, sizeof(updated_intake), 0);
						if (rec_stat < 0) {
							perror("Receiving Failed");
							return -1;
						}				
						update_stat = update_course_intake(course_id, updated_intake);
						printf("Updated Intake %d", updated_intake);
					} else {
						continue;
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
					
					int creg_stat = enroll_for_course(login_token.userid, cid);
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
					
					int cunen_stat = unenroll_from_course(login_token.userid, unen_id);
					send_stat = send(client, &cunen_stat, sizeof(cunen_stat), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
				} else if (stud_choice == 3) {
					int enrolled_c[80];
					int fd2 = open("student.txt", O_RDWR);
					for (int i = 0; i < 80; i++) {
						enrolled_c[i] = -1;
					}
					while (1) {
						struct Student temp;
						int read_stat = read(fd2, &temp, sizeof(temp));
						if (read_stat == 0) {
							break;
						} else if (temp.stud_id == login_token.userid) {
							for (int k = 0; k < 80; k++) {
								enrolled_c[k] = temp.courses[k];
							}
							break;
						}
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
					
					int s_pass_stat = change_stud_password(login_token.userid, s_new_pass);
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
