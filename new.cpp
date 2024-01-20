#include <iostream>
#include <vector>
#include <string>

using std :: cout;
using std :: endl;
using std :: string;
using std :: vector;

int main()
{
    vector<string> msg {"Hello", "World", "from", "C++", "!"};

    for (int i = 0; i < msg.size(); i++)
    {
        cout << msg[i] << " ";
    }
    cout << endl;
}