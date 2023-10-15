/// @file Student.cpp
/// @brief Allows for creation of Student objects implementing the person class.
/// @author Tyler Edwards - tk.edwards2003@gmail.com

#include "Student.h"

  Student::Student(){} //default constructor

  Student::Student(int studentId, string studentName, string studentLevel, string studentMajor, double studentGpa)
  { // overloaded constructor
    this->m_id = studentId;
    this->m_name = studentName;
    this->m_level = studentLevel;

    m_major = studentMajor;
    m_gpa = studentGpa;
    m_advisorId = -1;
  }

  Student::~Student(){} //destructor

  // prints the student's info
  //@input N/A
  //@output N/A
  void Student::printInfo()
  {
    string nameIdLevel = this->getNameIdAndLevel();
    cout << nameIdLevel << endl;

    cout << "Major: " << this->m_major << endl;
    cout << "GPA: " << this->m_gpa << endl;

    if(this->m_advisorId == -1)
    {
      cout << "NO ADVISOR YET" << endl;
    }
    else
    {
      cout << "Advisor ID: " << this->m_advisorId << endl;
    }
  }

  // returns the given student's advisor's id
  //@input N/A
  //@output int - advisor's id
  int Student::getAdvisor() {return this->m_advisorId;}

  // swaps the student's advisor
  //@input int - advisor's id
  //@output N/A
  void Student::swapAdvisor(int newId) {
    cout << "newId: " << newId << endl;
    m_advisorId = newId;
    }

  bool Student::operator ==(Student& rhs) //overloads the == operator
  {
    if (m_id == rhs.getId()){
      return true;
    }else{return false;}
  }

  bool Student::operator !=(Student& rhs) //overloads the != operator
  {return(m_id != rhs.getId());}

  bool Student::operator <(Student& rhs) //overloads the < operator
  {return(m_id < rhs.getId());}

  bool Student::operator >(Student& rhs) //overloads the > operator
  {return(m_id > rhs.getId());}
