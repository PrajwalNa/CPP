/***********************************************************************
// PROG36589 - Advanced Programming
// Workshop 5
// Version 1.0
// Author: Prajwal Nautiyal
/////////////////////////////////////////////////////////////////
***********************************************************************/

#include <iostream>
#ifndef SDDS_EMPLOYEE_H_
#define SDDS_EMPLOYEE_H_
#include "ReadWrite.h"
namespace sdds {
    class Employee : public ReadWrite {
        int m_empno;
        int m_office;
        char m_name[41];
        double m_salary;
    public:
        Employee();
        Employee(int stno, const char* name, double salary, int office);
        void set(int stno, const char* name, double salary, int office);
        std::ostream& display(std::ostream& os)const;
        std::istream& read(std::istream& is);
        bool operator==(int office)const;
    };


}
#endif // !SDDS_EMPLOYEE_H_