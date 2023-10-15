/// @file Faculty.cpp
/// @brief Allows for creation of Faculty objects implementing the person class.
/// @author Tyler Edwards - tk.edwards2003@gmail.com

#include "Faculty.h"

Faculty::Faculty(){} //default  constructor

Faculty::Faculty(int facultyId, string facultyName, string facultyLevel, string facultyDepartment) //overloaded constructor
{

  this->m_id = facultyId;
  this->m_name = facultyName;
  this->m_level = facultyLevel;

  m_department = facultyDepartment;
}

Faculty::~Faculty(){} //destructor

// prints the faculty member's info
//@input N/A
//@output N/A
void Faculty::printInfo()
{
  string nameIdLevel = this->getNameIdAndLevel();
  cout << nameIdLevel << endl;

  cout << "Department: " << this->m_department << endl;
  cout << "Advisee IDs" << endl;

  if(m_adviseesIds.isEmpty())
  {
    cout << "No advisees yet." << endl;
  }

  else
  {
    for(int i = 0; i < this->m_adviseesIds.size(); ++i)
    {
      cout << "Student " << i + 1 << ": " << this->m_adviseesIds.get(i) << endl;
    }
  }
}

// removes an advisee from the faculty given the student's id
//@input int - student's id
//@output N/A
void Faculty::removeAdvisee(int id)
{
  int pos = m_adviseesIds.search(id);
  cout << pos << endl;
  this->m_adviseesIds.remove(pos);
}

// adds an advisee from the faculty given the student's id
//@input int - student's id
//@output N/A
void Faculty::addAdvisee(int id)
{
  cout << "Id: " << id << endl;
  m_adviseesIds.addBack(id);
}

  bool Faculty::operator ==(Faculty& rhs) //overloads the == operator
  {return(m_id == rhs.getId());}

  bool Faculty::operator !=( Faculty& rhs) //overloads the != operator
  {return(m_id != rhs.getId());}

  bool Faculty::operator <(Faculty& rhs) //overloads the < operator
  {return(m_id < rhs.getId());}

  bool Faculty::operator >(Faculty& rhs) //overloads the > operator
  {return(m_id > rhs.getId());}
