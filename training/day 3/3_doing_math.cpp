#include <iostream>
using namespace std;

// this file explains how to create a variables, assign values to it, and do math with them


// arduino.cc/reference




bool checkIfEven(int num){
    int leftover = num % 2;

    if(leftover == 0){
        return true;
    }

    else{
        return false;
    }
}







int dividerWidth = 30;

int main(){
    cout << "Hello World\n";

    int myInt = 5;

    cout << myInt << '\n';
    cout << myInt + 4 << '\n';

    cout << myInt << '\n';

    myInt = myInt + 3;
    cout << myInt << '\n';

    myInt += 2;
    cout << myInt << '\n';

    myInt++;
    cout << myInt << '\n';






    for(int i = 0; i < dividerWidth; i++){
        cout << '-';
    }
    cout << '\n';





    float myFloat = 3.14;

    cout << myFloat << '\n';
    cout << myFloat + 4 << '\n';

    cout << myFloat << '\n';

    myFloat = myFloat + 3;
    cout << myFloat << '\n';

    myFloat += 2;
    cout << myFloat << '\n';

    myFloat++;
    cout << myFloat << '\n';




    for(int i = 0; i < dividerWidth; i++){
        cout << '-';
    }
    cout << '\n';




    cout << "\n\nmultiplication & div\n\n";


    cout << 10 + 2 << '\n';
    cout << 10 - 2 << '\n';
    cout << 10 / 2 << '\n';
    cout << 10 * 2 << '\n';
    cout << 10 % 2 << "\n\n"; // if there is a remainder, the number is even.
    cout << checkIfEven(10);

    cout << 10 / 3 << '\n';
    cout << 10 / 4 << '\n';
    cout << 10 / 3.0 << '\n';
    cout << 10.0 / 3 << '\n';
    cout << 10 / 4.0 << '\n';
    cout << 10.0 / 4 << '\n';




    for(int i = 0; i < dividerWidth; i++){
        cout << '-';
    }
    cout << '\n';

    cout << "\n\ncharacter stuff\n\n";


    char myLetter = 'A';
    cout << myLetter << endl << '\n';

    for(int i = 0; i < dividerWidth; i++){
        myLetter++;
        cout << myLetter << endl;
    }



    for(int i = 0; i < dividerWidth; i++){
        cout << '-';
    }
    cout << '\n';



    return 0;
}
