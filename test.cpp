# include <iostream>
using namespace std;

class MyClass {
    private:
        double value;
    public:
        MyClass(double v) : value(v) {}
        operator int() const { return static_cast<int>(value); }
        operator double() const { return value; }
};

int main() {
    MyClass obj(3.14);
    int i = obj; // calls operator int()
    double d = obj; // calls operator double()
    cout << i << endl;
    cout << d << endl;
    return 0;
}