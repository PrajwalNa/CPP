// Name: Prajwal Nautiyal
// Date: 2023/11/12

# include <iostream>
# include <cstring>
# include "RideRequest.h"

float g_taxrate = 0.00;
float g_discount = 0.00;

namespace sdds {

    RideRequest::RideRequest() {
        price = 0.00;
        customerName[0] = '\0';
        xtraDetails[0] = '\0';
        discount = false;
    }

    void RideRequest::read(std::istream& in) {
        char discCheck = '\0';
        if (!in.fail()) {
            in.getline(customerName, 10, ',');
            customerName[9] = '\0';
            in.getline(xtraDetails, 25, ',');
            xtraDetails[24] = '\0';
            in >> price;
            in.ignore();
            in >> discCheck;
            if (discCheck == 'Y'){
                discount = true;
            }
            else { discount = false; }
        }
    }

    void RideRequest::display() const {
        double priceTAX = price;
        priceTAX += price * g_taxrate;
        if (customerName[0] == '\0' || xtraDetails[0] == '\0' || price == 0.00) {
            std::cout << std::left;
            std::cout.width(2);    
            std::cout << counter << ". ";
            std::cout << "No Ride Request" << std::endl;
        }
        else{
            std::cout << std::left;
            std::cout.width(2);    
            std::cout << counter << ". ";
            std::cout.width(10);
            std::cout << std::left << customerName << '|';
            std::cout.width(25);
            std::cout << std::left << xtraDetails << '|';
            std::cout.width(12);
            std::cout << std::left;
            std::cout.setf(std::ios::fixed);
            std::cout.precision(2);
            std::cout << priceTAX << '|';
            std::cout.width(13);
            std::cout << std::right;
            if (discount)
                std::cout << priceTAX - g_discount;
            else
                std::cout << "";
            std::cout.unsetf(std::ios::fixed);
            std::cout << std::endl;
        }
        counter++;
    }
}
int sdds::RideRequest::counter = 1;