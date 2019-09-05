/*
 * pointers.cpp
 *
 *  Created on: Jan 30, 2017
 *      Author: Qiuan Wu
 *      Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <iostream>

using namespace std;

void display_array(int array[], const int length) {
    cout << "[";
    for (int i = 0; i < length; ++i) {
        if (i != 0) {
            cout << ", ";
        }
        cout << array[i];
    }
    cout << "]" << endl;
}

void display_array_ptr(int array[], const int length) {
    cout << "[";
    for (int *ptr = array, *end = array + length; ptr < end; ++ptr) {
        if (ptr != array) {
            cout << ", ";
        }
        cout << *ptr;
    }
    cout << "]" << endl;
}

void pass_by_value(int x) {
    x = 10;
}

void pass_by_pointer(int *x) {
    *x = 10;
}

void pass_by_reference(int &x) {
    x = 10;
}

int main() {
    int x = 5, y = 6, *z = &x;
    cout << z << endl;
    cout << *z << endl;
    cout << "x = " << x << ", " << "y = " << y << endl;
    *z = 7;
    cout << "x = " << x << ", " << "y = " << y << endl;
    z = &y;
    *z = 7;
    cout << "x = " << x << ", " << "y = " << y << endl;
    cout << ++z << endl; // BAD IDEA: We're not sure what z points to now.
    cout << *z << endl;
    z += 30000;          // TERRIBLE IDEA: z points outside the address space
                         // of this process.
    // *z = 20;          // Assigning a new value to the place z points will
                         // cause a segmentation fault.

    int* values = new int[y];
    for (int i = 0; i < y; i++) {
        values[i] = i;
    }
    display_array(values, y);
    display_array_ptr(values, y);
    delete [] values;

    x = 5;
    y = 6;
    pass_by_value(x);
    cout << "x = " << x << ", " << "y = " << y << endl;

    x = 5;
    y = 6;
    pass_by_pointer(&x);
    cout << "x = " << x << ", " << "y = " << y << endl;

    x = 5;
    y = 6;
    pass_by_reference(y);
    cout << "x = " << x << ", " << "y = " << y << endl;

    return 0;
}



