/***********************************************************************
// PROG36589 - Advanced Programming
// Workshop 5
// Version 1.0
// Author: Prajwal Nautiyal
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
#ifndef SDDS_CAR_H_
#define SDDS_CAR_H_
#include "ReadWrite.h"
namespace sdds {
    class Car : public ReadWrite {
        char m_plate[9];
        char m_makeModel[41];
    public:
        Car(const char* plate = "", const char* makeModel = "");
        void set(const char* plate, const char* makeModel);
        std::ostream& display(std::ostream& os)const;
        std::istream& read(std::istream& is);
        bool operator==(const char* mmSubstr)const;
    };


}
#endif // !SDDS_CAR_H_