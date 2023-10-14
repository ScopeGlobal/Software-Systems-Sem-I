#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(void) {

	int client;
	struct sockaddr_in server_addr;
	char buf[1024];
	
	client = socket(AF_INET, SOCK_STREAM, 0);
	if (client < 0) {
		perror("Server side Socket creation failed");
		return -1;
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5002);
	inet_pton(AF_INET, "172.24.120.60", &(server_addr.sin_addr));
	
	int connect_stat = connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (connect_stat < 0) {
		perror("Connection Failed");
		return -1;
	}
	struct {
		int choice;
		int userid;
		char password[80];
	} login_token;
	char choice[3];
	int admin_choice, student_choice, faculty_choice;
	
	printf("LOGIN PORTAL \n");
	printf("1. Create Student \n");
	printf("2. Create Faculty \n");
	printf("3. Student Login \n");
	printf("4. Faculty Login \n");
	printf("5. Admin Login \n");
	printf("Enter Choice- ");
	scanf("%d", &login_token.choice);
	while(getchar()!='\n');
	printf("\nEnter User ID- ");
	scanf("%d", &login_token.userid);
	printf("\n Enter Password- ");
	while(getchar()!='\n');
	scanf("%[^\n]", login_token.password);
	printf("\n");
	
	int send_stat = send(client, &login_token, sizeof(login_token), 0);
	if (send_stat < 0) {
		perror("Sending Failed");
		return -1;
	}
	
	char role;
	int rec_stat = recv(client, &role, sizeof(role), 0);
	if (rec_stat < 0) {
		perror("Receiving Failed");
		return -1;
	}
	
	switch (role) {
		case 'a':
			printf("You have logged in as Admin! \n");
			while (1) {
				printf("ADMIN PORTAL \n");
				printf("1. Add Student \n");
				printf("2. Add Faculty \n");
				printf("3. Activate/Deactivate Student \n");
				printf("4. Update Student \n");
				printf("5. Update Faculty \n");
				printf("6. Exit \n");
				
				printf("Enter your choice- ");
				scanf("%d", &admin_choice);
				
				send_stat = send(client, &admin_choice, sizeof(admin_choice), 0);
				if (send_stat < 0) {
					perror("Sending Failed");
					return -1;
				}
				
				if (admin_choice == 1) {
					struct {
						int stud_id;
						char stud_name[80];
						int num_courses;
						int courses[80];
						char password[80];
						char email[80];
						int activity_stat;
					} student;
					
					printf("Enter Student ID- ");
					scanf("%d", &student.stud_id);
					while(getchar() != '\n');
					printf("Enter Student Name- ");
					scanf("%[^\n]", student.stud_name);
					while(getchar() != '\n');
					printf("Enter Student Email- ");
					scanf("%[^\n]", student.email);
					student.num_courses = 0;
					for (int i = 0; i < 80; i++) {
						student.courses[i] = -1;
					}
					student.activity_stat = 0;
					strcpy(student.password, "student");
					send_stat = send(client, &student, sizeof(student), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int add_stat;
					rec_stat = recv(client, &add_stat, sizeof(add_stat), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					if (add_stat < 0) {
						printf("Student Adding Failed! \n");
					}
					else {
						printf("Student Added Successfully! \n");
					}
				} else if (admin_choice == 2) {
					struct {
						int fac_id;
						char fac_name[80];
						char email[80];
						char password[80];
						int num_courses;
						int courses[80];
					} faculty;
					
					printf("Enter Faculty ID- ");
					scanf("%d", &faculty.fac_id);
					while(getchar() != '\n');
					printf("Enter Faculty Name- ");
					scanf("%[^\n]", faculty.fac_name);
					while(getchar() != '\n');
					printf("Enter Faculty Email- ");
					scanf("%[^\n]", faculty.email);
					faculty.num_courses = 0;
					for (int i = 0; i < 80; i++) {
						faculty.courses[i] = -1;
					}
					strcpy(faculty.password, "faculty");
					
					send_stat = send(client, &faculty, sizeof(faculty), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int add_stat;
					rec_stat = recv(client, &add_stat, sizeof(add_stat), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					if (add_stat < 0) {
						printf("Faculty Addition Failed! \n");
					}
					else {
						printf("Faculty Added Successfully! \n");
					}
					
				} else if (admin_choice == 3) {
					int activate_id;
					printf("Enter the ID of the student to be activated- ");
					scanf("%d", &activate_id);
					send_stat = send(client, &activate_id, sizeof(activate_id), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int act_stat;
					rec_stat = recv(client, &act_stat, sizeof(act_stat), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}					
					if (act_stat < 0) {
						printf("Student Activation/Deactivation Failed \n");
					} else if (act_stat == 0 ){
						printf("Student Deactivated Successfully! \n");
					} else {
						printf("Student Activated Successfully! \n");
					}
					
				} else if (admin_choice == 4) {
					int student_id;
					printf("Enter the ID of the Student to be updated- ");
					scanf("%d", &student_id);
					send_stat = send(client, &student_id, sizeof(student_id), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int stud_update_choice;
					
					printf("UPDATE MENU \n");
					printf("1. Update Name \n");
					printf("2. Update Email \n");
					printf("3. Exit Menu \n");
					printf("Enter your choice- ");
					scanf("%d", &stud_update_choice);
					send_stat = send(client, &stud_update_choice, sizeof(stud_update_choice), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					char updated[80];
					if (stud_update_choice == 1) {
						while(getchar() != '\n');
						printf("Enter updated name- ");
						scanf("%[^\n]", updated);
					} else if (stud_update_choice == 2) {
						while(getchar() != '\n');
						printf("Enter updated email- ");
						scanf("%[^\n]", updated);
					} else {
						continue;
					}
					
					send_stat = send(client, updated, sizeof(updated), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}	
					
					int stud_upd_stat;
					rec_stat = recv(client, &stud_upd_stat, sizeof(stud_upd_stat), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					if (stud_upd_stat < 0) {
						printf("Student Update Failed \n");
					} else {
						printf("Student Update Successful! \n");
					}
					
				} else if (admin_choice == 5) {
					int faculty_id;
					printf("Enter the ID of the Faculty to be updated- ");
					scanf("%d", &faculty_id);
					send_stat = send(client, &faculty_id, sizeof(faculty_id), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int fac_update_choice;
					
					printf("UPDATE MENU \n");
					printf("1. Update Name \n");
					printf("2. Update Email \n");
					printf("3. Exit Menu \n");
					printf("Enter your choice- ");
					scanf("%d", &fac_update_choice);
					send_stat = send(client, &fac_update_choice, sizeof(fac_update_choice), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					char updated_fac[80];
					if (fac_update_choice == 1) {
						printf("Enter updated name- ");
						while(getchar()!= '\n');
						scanf("%[^\n]", updated_fac);
					} else if (fac_update_choice == 2) {
						printf("Enter updated email- ");
						while(getchar()!='\n');
						scanf("%[^\n]", updated_fac);
					} else {
						continue;
					}
					
					send_stat = send(client, updated_fac, sizeof(updated_fac), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}	
					
					int fac_upd_stat;
					rec_stat = recv(client, &fac_upd_stat, sizeof(fac_upd_stat), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					if (fac_upd_stat < 0) {
						printf("Faculty Update Failed \n");
					} else {
						printf("Faculty Update Successful! \n");
					}
					
				} else {
					break;
				}
				
				
			}
			break;
		case 'f':
			printf("You have logged in as Faculty! \n");
			while (1) {
				int fac_choice;
				printf("FACULTY MENU \n");
				printf("1. Add New Course \n");
				printf("2. Remove Course \n");
				printf("3. View Enrollments in Courses \n");
				printf("4. Change Password \n");
				printf("5. Update Course Details \n");
				printf("6. Exit \n");
				printf("Enter your choice- ");
				scanf("%d", &fac_choice);
				
				send_stat = send(client, &fac_choice, sizeof(fac_choice), 0);
				if (send_stat < 0) {
					perror("Sending Failed");
					return -1;
				}
				
				if (fac_choice == 1) {
					struct {
						int course_id;
						char course_name[80];
						int intake;
						int enroll_count;
						int enrolled[150];
						int course_status;
					} course;
					
					printf("Enter Course ID- ");
					scanf("%d", &course.course_id);
					while(getchar() != '\n');
					printf("Enter Course Name- ");
					scanf("%[^\n]", course.course_name);
					while(getchar()!='\n');
					printf("Enter Course Intake- ");
					scanf("%d", &course.intake);
					course.enroll_count = 0;
					for (int i = 0; i < 150; i++) {
						course.enrolled[i] = -1;
					}
					course.course_status = 1;
					
					send_stat = send(client, &course, sizeof(course), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int cadd_stat;
					rec_stat = recv(client, &cadd_stat, sizeof(cadd_stat), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					if (cadd_stat < 0) {
						printf("Course Addition Failed! \n");
					}
					else {
						printf("Course Added Successfully! \n");
					}
					
					
				} else if (fac_choice == 2) {
				
					int del_id;
					printf("Enter the ID of the Course to be deleted- ");
					scanf("%d", &del_id);
					
					send_stat = send(client, &del_id, sizeof(del_id), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int cdel_stat;
					rec_stat = recv(client, &cdel_stat, sizeof(cdel_stat), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					if (cdel_stat < 0) {
						printf("Course Deletion Failed! \n");
					}
					else {
						printf("Course Deleted Successfully! \n");
					}
					
				} else if (fac_choice == 3) {
					int co_id;
					printf("Enter the Course ID of the Course you want to list the Enrollees for- ");
					scanf("%d", &co_id);
					send_stat = send(client, &co_id, sizeof(co_id), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int enrollees[150];
					rec_stat = recv(client, enrollees, sizeof(enrollees), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}						
					
					if (enrollees[0] == -1) {
						printf("No students have enrolled for this course! \n");
					} else {
						int i = 0;
						printf("The following Student IDs have enrolled- \n");
						while (enrollees[i] != -1) {
							printf("%d \n", enrollees[i]);
							i++;
						}
					}
					
				} else if (fac_choice == 4) {
					
					char new_pass[80];
					while(getchar()!='\n');
					printf("Enter New Password- ");
					scanf("%[^\n]", new_pass);
					
					send_stat = send(client, new_pass, sizeof(new_pass), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int pass_stat;
					rec_stat = recv(client, &pass_stat, sizeof(pass_stat), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					if (pass_stat < 0) {
						printf("Password Change Failed! \n");
					}
					else {
						printf("Password Changed Successfully! \n");
					}
					
				} else if (fac_choice == 5) {
					int course_id;
					while(getchar() != '\n');
					printf("Enter the ID of the Course to be updated- ");
					scanf("%d", &course_id);
					send_stat = send(client, &course_id, sizeof(course_id), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int course_update_choice;
					
					printf("UPDATE MENU \n");
					printf("1. Update Name \n");
					printf("2. Update Intake \n");
					printf("3. Exit Menu \n");
					printf("Enter your choice- ");
					scanf("%d", &course_update_choice);
					while(getchar() != '\n');
					send_stat = send(client, &course_update_choice, sizeof(course_update_choice), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					printf("Update choice: %d\n", course_update_choice);
					char updated_course[80];
					if (course_update_choice == 1) {
						// while(getchar()!= '\n');
						printf("Enter updated name- ");
						// printf("I am here\n");
						scanf("%s", updated_course);
						printf("I got what you want\n");
						send_stat = send(client, updated_course, sizeof(updated_course), 0);
						if (send_stat < 0) {
							perror("Sending Failed");
							return -1;
						}
						printf("I sent that\n");
					} else if (course_update_choice == 2) {
						int updated_intake;
						printf("Enter updated Intake- ");
						while(getchar()!='\n');
						scanf("%d", &updated_intake);
						send_stat = send(client, &updated_intake, sizeof(updated_intake), 0);
						if (send_stat < 0) {
							perror("Sending Failed");
							return -1;
						}
					} else {
						continue;
					}
						
					
					int course_upd_stat;
					rec_stat = recv(client, &course_upd_stat, sizeof(course_upd_stat), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					if (course_upd_stat < 0) {
						printf("Course Update Failed \n");
					} else {
						printf("Course Update Successful! \n");
					}
					
				} else {
					break;
				}
				
			}
			break;
		case 's':
			printf("You have logged in as Student \n");
			while (1) {
				int stud_choice;
				printf("STUDENT MENU \n");
				printf("1. Enroll to a Course \n");
				printf("2. Unenroll from a Course \n");
				printf("3. View Enrolled Courses \n");
				printf("4. Change Password \n");
				printf("5. Exit \n");
				printf("Enter your choice- ");
				scanf("%d", &stud_choice);
				
				send_stat = send(client, &stud_choice, sizeof(stud_choice), 0);
				if (send_stat < 0) {
					perror("Sending Failed");
					return -1;
				}
				
				if (stud_choice == 1) {
					int cid;
					printf("Enter the ID of the Course you wish to enroll to- ");
					scanf("%d", &cid);
					send_stat = send(client, &cid, sizeof(cid), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int creg_stat;
					rec_stat = recv(client, &creg_stat, sizeof(creg_stat), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					if (creg_stat < 0) {
						printf("Course Registration Failed! \n");
					}
					else {
						printf("Registered for Course Successfully! \n");
					}
					
					
				} else if (stud_choice == 2) {
				
					int unen_id;
					printf("Enter the ID of the Course to Unenroll from- ");
					scanf("%d", &unen_id);
					
					send_stat = send(client, &unen_id, sizeof(unen_id), 0);
					printf("Sent id %d\n", unen_id);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int cunen_stat;
					printf("Waiting to receive response\n");
					rec_stat = recv(client, &cunen_stat, sizeof(cunen_stat), 0);
					printf("Response received: %d\n", rec_stat);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					if (cunen_stat < 0) {
						printf("Course Unenrollment Failed! \n");
					}
					else {
						printf("Course Unenrolled from Successfully! \n");
					}
					
				} else if (stud_choice == 3) {
					
					int enrolled_c[150];
					rec_stat = recv(client, enrolled_c, sizeof(enrolled_c), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}						
					
					if (enrolled_c[0] == -1) {
						printf("You have not enrolled for any courses! \n");
					} else {
						int i = 0;
						printf("You have enrolled for the Following Course IDs- \n");
						while (enrolled_c[i] != -1) {
							printf("%d \n", enrolled_c[i]);
							i++;
						}
					}
					
				} else if (stud_choice == 4) {
					
					char s_new_pass[80];
					while(getchar()!='\n');
					printf("Enter New Password- ");
					scanf("%[^\n]", s_new_pass);
					
					send_stat = send(client, s_new_pass, sizeof(s_new_pass), 0);
					if (send_stat < 0) {
						perror("Sending Failed");
						return -1;
					}
					
					int s_pass_stat;
					rec_stat = recv(client, &s_pass_stat, sizeof(s_pass_stat), 0);
					if (rec_stat < 0) {
						perror("Receiving Failed");
						return -1;
					}
					
					if (s_pass_stat < 0) {
						printf("Password Change Failed! \n");
					}
					else {
						printf("Password Changed Successfully! \n");
					}
					
				} else {
					break;
				}
							
			}
			break;
		default:
			printf("Auth failed! \n");	
			break;
	}
	
	close(client);
	
	return 0;
}
