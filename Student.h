/// @file Student.h
/// @brief Allows for creation of Student objects implementing the person class. (header)
/// @author Tyler Edwards - tk.edwards2003@gmail.com

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
using namespace std;

#include "Person.h"
#include "DblList.h"

class Student : public Person //inherits from Person abstract class
{
  private:
    string m_major;
    double m_gpa;
    int m_advisorId;

  public:
    Student(); //default constructor
    Student(int studentId, string studentName, string studentLevel, string studentMajor, double studentGpa); //overloaded constructor
    virtual ~Student(); //destructor
    void printInfo(); //prints the student's info
    int getAdvisor(); //returns the id of the advisor
    void swapAdvisor(int newId); //changes the advisor given the id

    bool operator ==(Student& rhs); //overloads the == operator
    bool operator !=(Student& rhs); //overloads the != operator
    bool operator <(Student& rhs); //overloads the < operator
    bool operator >(Student& rhs); //overloads the > operator

};

#endif
