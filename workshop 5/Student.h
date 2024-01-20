/***********************************************************************
// PROG36589 - Advanced Programming
// Workshop 5
// Version 1.0
// Author: Prajwal Nautiyal
/////////////////////////////////////////////////////////////////
***********************************************************************/

#include <iostream>
#ifndef SDDS_STUDENT_H_
#define SDDS_STUDENT_H_
#include "ReadWrite.h"
namespace sdds {
    class Student : public ReadWrite {
        int m_stno;
        char m_name[41];
        double m_gpa;
    public:
        Student();
        Student(int stno, const char* name, double gpa);
        void set(int stno, const char* name, double gpa);
        std::ostream& display(std::ostream& os)const;
        std::istream& read(std::istream& is);
        bool operator==(double gpa)const;
    };
}
#endif // !SDDS_STUDENT_H_
