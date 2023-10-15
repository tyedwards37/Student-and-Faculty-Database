#READ.ME

Project: Student and Faculty Database
by Tyler Edwards and Ryan Jewik
Added October 2023

Description: Using trees with node implementation, create a database of students and faculty. Using this database the user is able to print, find, display, add, and delete student/faculty information. After one of these actions is taken, the program will return the user to the options menu and prompt them again. Once the user is done with the database, they can choose to exit out of the program. However, this database does not currently persist outside of the program, so once exited, it is reset. 

Language: C++

Reason: For CPSC 350 (Data Structures)

Successes: Got to practice working together with someone on a large scale project, with lots of different moving parts. This required communication on both o four parts and making sure that we kept versions up to date while we both worked on different files.

Setbacks: Though I understood trees fundemantally, understanding and implementing them within a practical setting was much more difficult.

Learned: practical application of trees, use of nodes


/*
Commands:
g++ *.cpp -o execute
./execute

Output:
Hello! Welcome to the Student and Faculty Database.

Please select an option below: 
1 - Print all students and their information
2 - Print all faculty and their information
3 - Find and display student information given the students id
4 - Find and display faculty information given the faculty id
5 - Add a new student
6 - Delete a student given the id
7 - Add a new faculty member
8 - Delete a faculty member given the id.
9 - Change a student’s advisor given the student id and the new faculty id.
10 - Remove an advisee from a faculty member given the ids.
11 - Exit.
*/

- Started from in-class base code
