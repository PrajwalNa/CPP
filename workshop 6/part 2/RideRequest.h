// Name: Prajwal Nautiyal
// Date: 2023/11/12

# ifndef SDDS_RIDEREQUEST_H
# define SDDS_RIDEREQUEST_H
# include <iostream>

extern float g_taxrate;
extern float g_discount;

namespace sdds{

    class RideRequest{
        double price;
        static int counter;
        char customerName[10];
        char* xtraDetails;
        bool discount;
        public:
            RideRequest();
            void read(std::istream& in);
            void display() const;
            ~RideRequest();
    };
}
#endif