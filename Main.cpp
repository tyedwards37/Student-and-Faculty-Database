/// @file Main.cpp
/// @brief Runs the database system.
/// @author Tyler Edwards - tk.edwards2003@gmail.com

#include <string>
#include <iostream>
using namespace std;

#include "Student.h"
#include "Faculty.h"
#include "ScapegoatST.h"

int main()
{
  int input;
  bool done = false;
  cout << "Hello! Welcome to the Student and Faculty Database." << endl;
    ScapegoatST<Student> students;
    ScapegoatST<Faculty> faculty;
    int id;
    string name;
    string level;
    string major;
    double gpa;
    int advisor;
    string department;

    int s_id;
    int f_id;

    char confirm;


  while(!done)
  {
    cout << endl << "Please select an option below: " << endl;

    cout << "1 - Print all students and their information" << endl;
    cout << "2 - Print all faculty and their information" << endl;
    cout << "3 - Find and display student information given the students id" << endl;
    cout << "4 - Find and display faculty information given the faculty id" << endl;
    cout << "5 - Add a new student" << endl;
    cout << "6 - Delete a student given the id" << endl;
    cout << "7 - Add a new faculty member" << endl;
    cout << "8 - Delete a faculty member given the id." << endl;
    cout << "9 - Change a student’s advisor given the student id and the new faculty id." << endl;
    cout << "10 - Remove an advisee from a faculty member given the ids." << endl;
    cout << "11 - Exit." << endl;

    cin >> input;
    cout << endl;




    switch(input)
    {
      case 1: //print students
      {
        //cout <<students.getRoot()<<endl;
        students.ascArray(students.getRoot());

        break;
      }

      case 2: //print faculty
      {
        faculty.ascArray(faculty.getRoot());

        break;
      }

      case 3: //print specific student
      {
        cout << "Please enter ID of the student: " << endl;
        cin >> id;

        bool sinSystem = students.contains(id);
        while(sinSystem == false)
        {
          cout << "There is no student with that ID. Please enter a new ID: " << endl;
          cin >> id;
          sinSystem = students.contains(id);

        }

          cout << "Found them!" << endl;
          students.getPerson(id)->printInfo();


        break;
      }

      case 4: //print specific faculty
      {
        cout << "Please enter ID of the faculty member: " << endl;
        cin >> id;

        bool finSystem = faculty.contains(id);
        while(finSystem == false)
        {
          cout << "There is no student with that ID. Please enter a new ID: " << endl;
          cin >> id;
          finSystem = students.contains(id);


        }

          cout << "Found them!" << endl;
          faculty.getPerson(id)->printInfo();


        break;
      }

      case 5: //add student
      {
        cout << "Please enter ID: ";
        cin >> id;

        cout << "Please enter name: ";
        cin >> name;
        string addName;
        getline(cin, addName);
        name += addName;

        cout << "Please enter level: ";
        cin >> level;

        cout << "Please enter major: ";
        cin >> major;
        string addMajor;
        getline(cin, addMajor);
        major += addMajor;

        cout << "Please enter GPA: ";
        cin >> gpa;
        cout << endl;

        Student sAdd(id, name, level, major, gpa);
        sAdd.printInfo();
        students.insert(sAdd);
        break;
      }

      case 6: //remove student
      {
        cout << "Please enter ID of student to delete: " << endl;
        cin >> id;

        while(!(students.contains(id)))
        {
          cout << "There is no student with that ID. Please enter a new ID: " << endl;
          cin >> id;


        }

          cout << "Found them!" << endl;

        students.getPerson(id)->printInfo();

        cout << "Delete this user? y/n" << endl;
        cin >> confirm;

        while(confirm != 'y' && confirm != 'n')
        {
          cout << "Please enter a valid letter: " << endl;
          cin >> confirm;
        }

        if(confirm == 'y')
        {


          if (students.getPerson(id)->getAdvisor() != -1){
          faculty.getPerson(students.getPerson(id)->getAdvisor())->removeAdvisee(id);
          }

          students.removeInt(id);
        }
        else {cout << "This student has not been deleted." << endl;}
        break;

      }

      case 7: //add faculty
      {
        cout << "Please enter ID: ";
        cin >> id;

        cout << "Please enter name: ";
        cin >> name;
        string addName;
        getline(cin, addName);
        name += addName;

        cout << "Please enter level: ";
        cin >> level;
        string addLevel;
        getline(cin, addLevel);
        level += addLevel;

        cout << "Please enter department: ";
        cin >> department;
        string addDepartment;
        getline(cin, addDepartment);
        department += addDepartment;

        Faculty fAdd(id, name, level, department);
        fAdd.printInfo();
        faculty.insert(fAdd);
        break;
      }

      case 8: //remove faculty
      {
         {
        cout << "Please enter ID of a faculty member to delete: " << endl;
        cin >> id;

        while(!(faculty.contains(id)))
        {
          cout << "There is no faculty member with that ID. Please enter a new ID: " << endl;
          cin >> id;

        }

        cout << "Found them!" << endl;

        faculty.getPerson(id)->printInfo();

        cout << "Delete this user? y/n" << endl;
        cin >> confirm;

        while(confirm != 'y' && confirm != 'n')
        {
          cout << "Please enter a valid letter: " << endl;
          cin >> confirm;
        }

        if(confirm == 'y')
        {
          for(int i = 0; i < faculty.getPerson(id)->m_adviseesIds.size(); ++i)
          {
            int tempStudent = faculty.getPerson(id)->m_adviseesIds.get(i);

            int newId;
            if(faculty.getMin().getId() != id)
            {newId = faculty.getMin().getId();}

            else
            {newId = faculty.getMax().getId();}

            students.getPerson(tempStudent)->swapAdvisor(newId);
          }

          faculty.removeInt(id);
        }

        else {cout << "This faculty has not been deleted." << endl;}

        break;

      }
      }

      case 9: //changing student advisor
      {
        cout << "Please enter ID of the student that you would like to change the advisor of: " << endl;
        cin >> s_id;

        while(!(students.contains(s_id)))
        {
          cout << "There is no student with that ID. Please enter a new ID: " << endl;
          cin >> s_id;


        }

          cout << "Found them!" << endl;

        students.getPerson(s_id)->printInfo();

        cout << "Please enter ID of the new faculty adivsor of this student: " << endl;
        cin >> f_id;

        while(!(faculty.contains(f_id)))
        {
          cout << "There is no faculty member with that ID. Please enter a new ID: " << endl;
          cin >> f_id;


        }

          cout << "Found them!" << endl;

        faculty.getPerson(f_id)->printInfo();

        cout << "Is this the correct student and faculty advisor? y/n" << endl;
        cin >> confirm;

        while(confirm != 'y' && confirm != 'n')
        {
          cout << "Please enter a valid letter: " << endl;
          cin >> confirm;
        }

        if(confirm == 'y')
        {
          if (students.getPerson(s_id)->getAdvisor() != -1){
          faculty.getPerson(students.getPerson(s_id)->getAdvisor())->removeAdvisee(s_id);
          }
          students.getPerson(s_id)->swapAdvisor(f_id);
          faculty.getPerson(f_id)->addAdvisee(s_id);
        }
        else {cout << "The faculty advisor has not been changed." << endl;}

        break;
      }

      case 10: //removing advisee
      {
        cout << "Please enter ID of the faculty member you'd like to remove the advisee from: " << endl;
        cin >> f_id;

        while(!(faculty.contains(f_id)))
        {
          cout << "There is no faculty member with that ID. Please enter a new ID: " << endl;
          cin >> f_id;


        }

          cout << "Found them!" << endl;

        faculty.getPerson(f_id)->printInfo();

        cout << "Please enter ID of the advisee you would like to remove: " << endl;
        cin >> s_id;

        while(!(students.contains(s_id)))
        {
          cout << "There is no student with that ID. Please enter a new ID: " << endl;
          cin >> s_id;


        }

          cout << "Found them!" << endl;

        students.getPerson(s_id)->printInfo();

        cout << "Is this the correct student and faculty advisor? y/n" << endl;
        cin >> confirm;

        while(confirm != 'y' && confirm != 'n')
        {
          cout << "Please enter a valid letter: " << endl;
          cin >> confirm;
        }

        if(confirm == 'y')
        {

          int newId;
          if(faculty.getMin().getId() != f_id)
          {
           newId = faculty.getMin().getId();
           faculty.getPerson(f_id)->removeAdvisee(s_id);
           students.getPerson(s_id)->swapAdvisor(newId);
           faculty.getPerson(newId)->addAdvisee(s_id);
          }

          else if (faculty.getMax().getId() != f_id)
          {
            newId = faculty.getMax().getId();
           faculty.getPerson(f_id)->removeAdvisee(s_id);
           students.getPerson(s_id)->swapAdvisor(newId);
           faculty.getPerson(newId)->addAdvisee(s_id);
          }
        }
        else {cout << "The advisee has not been removed because there were no other advisors." << endl;}

        break;
      }

      case 11: //exit
      {
        cout << "Goodbye! :)" << endl;
        done = true;
        break;
      }

      default:
      {
        cout << "That's not a valid number. Please type a different input:" << endl;
        cin >> input;
        break;
      }
    } // switch statement
  } // while loop
}
