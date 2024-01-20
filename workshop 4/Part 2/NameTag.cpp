/*
File: NameTag.cpp
Header file: NameTag.h
Version: 1.0
Date: 2023/10/15
Author: Prajwal Nautiyal
*/

# include "NameTag.h"
# include <cstring> // strlen, strcpy, strncpy
using namespace std;

namespace fast{

// default constructor
NameTag::NameTag() {
    m_name = nullptr;
    m_number = 0;
}

// one argument constructor
NameTag::NameTag(const char* name) {
    // if name is not null, set the name using the function setName
    if (name != nullptr) {
        setName(name);
    }
    // else allocate memory for m_name for the default output and copy "Empty NameTag" into it
    else {
        m_name = new char[strlen("Empty NameTag") + 1];
        strcpy(m_name, "Empty NameTag");
    }
    // set m_number to 0 since no number was provided
    m_number = 0;
}

// two argument constructor
NameTag::NameTag(const char* name, int number) {
    // again, if name is not null, set the name using the function setName
    if (name != nullptr) {
        setName(name);
        // if number is between 10000 and 99999, set m_number to number, else set it to -1
        // -1 is used to indicate that the number is invalid
        // while 0 is used to indicate that the number is not provided
        m_number = number > 10000 && number < 99999 ? number : -1;
    }
    // else allocate memory for m_name for the default output and copy "Empty NameTag" into it
    else {
        m_name = new char[strlen("Empty NameTag") + 1];
        strcpy(m_name, "Empty NameTag");
        // set m_number to -1 since the name is invalid
        m_number = -1;
    }
}

// destructor
NameTag::~NameTag() {
    delete[] m_name;
    m_name = nullptr;
}

// setName function
void NameTag::setName(const char* name){
    // if the number of characters is less than 40, allocate memory for m_name as the length of the string provided
    // else allocate memory for m_name as 40 characters
    int size = strlen(name) < 40 ? strlen(name) + 1 : 41;
    m_name = new char[size];
    // copy the string provided into m_name, if the length of the string is greater than 40, copy only the first 40 characters
    strlen(name) < 40 ? strcpy(m_name, name) : strncpy(m_name, name, 40);
    // set the last character of m_name to '\0'
    m_name[size-1] = '\0';
}

// read function
NameTag& NameTag::read() {
    // name[100]: to store the name provided by the user 
    // *charCheck: to check if the user entered a character which is not '\n' after tha integer
    char name[100], *charCheck;
    // clear any trailing characters in the input buffer, learnt this while trying to figure out a way to fix repeated output
    // citation: https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
    cin.sync();
    cout << "Enter name: ";
    
    invalidName:
    cin.getline(name, 100, '\n');
    m_name = new char[41]; // allocate memory for m_name as the maximum length of the name
    strncpy(m_name, name, 40); // only copy the first 40 characters of the name provided
    m_name[40] = '\0'; // set the last character of m_name to '\0'
    if (m_name[0] == '\0') { // if the first character of m_name is '\0', meaning the user did not enter anything
        cout << "Invalid Name, try again: ";
        goto invalidName; // go read from the input buffer again
    }

    cout << "Would you like to enter an extension? (Y)es/(N)o: "; // ask the user if they want to enter an extension
    
    extQ:
    cin >> charCheck; // read the response

    // if the user entered more than one character, meaning they entered more than just 'Y' or 'N', ask them to enter again
    if (strlen(charCheck) > 1) {
        cout << "Invalid response, try again: ";
        cin.clear(); // clear any error states
        cin.ignore(INT_MAX, '\n'); // clear the input buffer, citation: https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/, https://www.stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer
        goto extQ;
    }

    // check if the user entered 'Y' or 'y' or 'N' or 'n', if not, ask them to enter again
    // learnt switch case in high school, while learning Java
    switch (*charCheck) {
    // fallthrough
    case 'Y':
    case 'y':
        cout << "Enter a 5 digit extension: ";
        break;

    // fallthrough
    case 'N':
    case 'n':
        m_number = 0; // set m_number to 0 to indicate that the user did not enter a number
        goto extEnd;  // go to the end of the function
        break;

    default:
        cout << "Invalid response, try again: ";
        goto extQ;
        break;
    }

    invalidNum:
        cin >> m_number; // read the number provided by the user
        *charCheck = cin.get(); // read the character after the number
        // if user did not enter an integer or the character after the integer is not '\n', ask them to enter again
        if (cin.fail() || *charCheck != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Bad integer value, try again: ";
            goto invalidNum;
        }
        else // if the user entered a valid integer, check if it is between 10000 and 99999, if not, ask them to enter again
        if (m_number<=10000 || m_number>=99999) {
            cout << "Invalid value [10000<=value<=99999]: ";
            goto invalidNum;
        }
    extEnd:
    return *this;
}

std::ostream& NameTag::print() const {
    std :: ostream &os = std :: cout;
    
    int field; // to store the length of the field, min 20

    // check if m_name is not null
    if (m_name != nullptr) {
        // if the length of m_name is less than 20, set field to 20, else set it to the length of m_name
        field = strlen(m_name) < 20 ? 20 : strlen(m_name) + 1;
    }
    else {
        field = 20;
    }

    // check if m_name and m_number are not null and -1 respectively, if they are, print Empty NameTag
    if (m_name != nullptr && m_number != -1) {
        // print header
        os << "+";
        for (int i = 0; i < field + 2; i++) {
            os << "-";
        }
        os << "+" << endl;
        // print a blank line
        prn(" ", field);
        // print the name
        prn(m_name, field);
        // print a blank line
        prn(" ", field);
        // print the number
        os << "| ";
        // set the width of the field to the length of "Extension: "
        os.width(strlen("Extension: "));
        os.setf(ios::left);
        // print "Extension: " in the field
        os << "Extension: ";
        os.setf(ios::left);
        // set the width to the length of the field - the length of "Extension: "
        os.width(field - strlen("Extension: "));
        // check if m_number is not 0, if it is, print N/A, else print the number
        if (m_number != 0){
            os << m_number << " |" << endl;
        }
        else {
            os << "N/A" << " |" << endl;
        }
        // print a blank line
        prn(" ", field);
        // print the footer
        os << "+";
        for (int i = 0; i < field + 2; i++) {
            os << "-";
        }
        os << "+" << endl;
    }
    else {
        os << "Empty NameTag!!" << endl;
    }
    return os;
}

// prn function, prints a string in a field of a given length
void NameTag :: prn(const char str[], const int length) const {
    cout << "| ";
    cout.width(length);
    cout.setf(ios::left);
    cout << str;
    cout << " |" << endl;
}

}