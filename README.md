# Software Systems (SS-513)

This Repository contains the full set of Assignments Projects, assigned as a part of course **CS 513, M. Tech, Sem 1**.

## Hands On List 1

Includes a set of questions based on file opening, read and write to a file, a set of dedicated system calls, File locking, Process Management and Daemon Processes. 

## Hands On List 2

Includes a further set of questions based on Pipes, IPC mechanisms (Message Queues, Shared Memory, Semaphores), SOcket Programming and Concurrent Servers. 

## Mini Project

**Course Registration Academia Portal** using Socket Programming in C.
 Concepts used - File Opening, File Reading, File Writing, File Closing, File Locking, lseek system call, fcntl system call, Socket Programming. 

 The project involves three different types of users, 
 - Admin
 - Faculty
 - Student

 each with their, own Unique functionalities.

 ### Admin

 On project initialization, it is required to run the `admin.c` file using the following terminal commands:

 - ``gcc admin.c -o a.out``<br>
 - ``./a.out``

 An admin for the project will be created on execution. Once created, the Admin can do the following:

 - Add a new Student
 - Add a new Faculty Member
 - Activate/Deactivate a Student
 - Update Student
 - Update Faculty

 ### Faculty

 Faculty members, once created by the Admin can perform the following tasks-

 - Add a Course
 - Remove a Course
 - View all the Students enrolled for a particular Course
 - Update a Course
 - Change Password

 It is to be noted that updating a course involves changing the Intake as well. Students may be unenrolled depending on the Intake Change.

 > For example, if a Course has 145 students enrolled, with an intake of 150, and the intake is reduced to 140, the last 5 (150 - 145) students who enrolled to the course, will be unenrolled from it. The Course will also no longer appear in the list of courses a student has enrolled for. 

 Removing a Course will lead to all Students enrolled in it being unenrolled. The Course will also be removed from the list of courses taught by the faculty who removed it.

 ### Student

 A Student member, once created by an Admin can perform the following tasks-

 - Enroll for a Course
 - Unenroll from a Course
 - View all Courses they enrolled for
 - Change Password

 ### Running the Project

 Being a Socket Program, the Project consists of two separate programs, `client.c` and `server.c`. After running `admin.c`, the project can be run using the following sequence of commands-

 > `gcc server.c -o s.out`<br>
 > `./s.out`

 Now, open another terminal and run the following:

 > `gcc client.c -o c.out`<br>
 > `./c.out`

 If the Program, on first run, throws up a `Binding Failure` error, it is advisable to change the Port Number the server runs on. This can be configured via the `server.c` file.

 ## Author

Created by-

- Sridhar Menon
- MT2023157
- IIIT Bangalore
