#pragma once
#include <iostream>
#include "Collection.h"
using namespace sdds;

/*
No cpp file as we are using templates,
And C++ requires the template definitions to be available to the compiler at compile time.
That means the template function definitions must be in the header file.
*/

template<typename T, typename N>
bool search(Collection<T>& typeOne, T arr[], int size, const N& typeTwoKey) {
    bool matchFound = false;
    // search the array for the key by iterating over the array elements
    for (int i = 0; i < size; i++) {
        // compare the two classes using the == operator overloaded in the respective classes
        // Car //
        // overloaded operator conducts a strstr() search on the make & model attribute of the car object
        // with the provided key, i.e., it looks for any substring match in the make & model attribute
        // Student //
        // In the Student class, the overloaded operator checks if the key is within 0.001 of the gpa i.e., key - 0.001 < gpa < key + 0.001
        // so basically, it checks if the key == gpa
        // Employee //
        // Here it just checks if the key == office number since office number is an integer
        if (arr[i] == typeTwoKey) {
            // if the key is found, add the element to the collection
            typeOne.add(arr[i]);
            // set the found flag to true
            matchFound = true;
        }
        // if the key is not found, the default initialisation of the found flag is false is returned
    }
    return matchFound;
}

template<typename T>
void listArrayElements(const char* title, const T arr[], int size) {
    // display the title
    std::cout << title << std::endl;
    // iterate over the array elements and display them one by one with their index
    for (int i = 0; i < size; i++) {
        std::cout << i + 1 << ": " << arr[i] << std::endl;
    }
}