/// @file Faculty.h
/// @brief Allows for creation of Faculty objects implementing the person class. (header)
/// @author Tyler Edwards - tk.edwards2003@gmail.com

#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <iostream>
using namespace std;

#include "Person.h"
#include "DblList.h"

class Faculty : public Person //inherits from Person abstract class
{
  private:
    string m_department;

  public:
    DblList<int> m_adviseesIds; // DoubleList of advisee IDs
    Faculty(); //default constructor
    Faculty(int facultyId, string facultyName, string facultyLevel, string facultyDepartment); //overloaded constructor
    virtual ~Faculty(); //destructor
    void printInfo(); //prints the Faculty's info
    void removeAdvisee(int id); //removes an advisee given the id
    void addAdvisee(int id); //adds an advisee given the id

    bool operator ==(Faculty& rhs); //overloads the == operator
    bool operator !=( Faculty& rhs); //overloads the != operator
    bool operator <(Faculty& rhs); //overloads the < operator
    bool operator >(Faculty& rhs); //overloads the > operator

    };



#endif
