/// @file Person.h
/// @brief Abstract class that helps define the basis in which a faculty or student is based. (header)
/// @author Tyler Edwards - tk.edwards2003@gmail.com

#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person //abstract class to be overloaded
{
  protected:
    int m_id;
    string m_name;
    string m_level;

  public:
    virtual void printInfo() = 0;

    string getNameIdAndLevel() const //returns the name, level, and id of the person
    {
      return this->m_name + ", " + this->m_level + ", " + to_string(this->m_id);
    }

    int getId() {return this->m_id;} //returns the person's id
};

#endif
