#include <iostream>
#include <limits>

using namespace std;

void errorMessage () {
    cout << "Invalid Input" << endl;
}

void intput_xyz (int& x, int& y, int& z){
    int int_input;
    cout << endl << "Set x: ";
    cin >> int_input;
    while (!cin) {
        errorMessage();
        cout << "Set x: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> int_input;
    }
    x = int_input;
    cout << "Set y: ";
    cin >> int_input;
    while (!cin) {
        errorMessage();
        cout << "Set y: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> int_input;
    }
    y = int_input;

    cout << "Set z: ";
    cin >> int_input;
    while (!cin) {
        errorMessage();
        cout << "Set z: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> int_input;
    }
    z = int_input;
}
