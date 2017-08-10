#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// this is a single line comment

/*
this is a multi line comment
line 2

comments are text that is not executed. They are purely here for you to explain your code to yourself and others. Use these while you code unless you enjoy painful experiences.

Over time you'll learn what comments are most helpful for you.

For now, watch my style.
Lots of code is design and style, not like analog circuits which have a small limited number of ways to hook up a pushbutton safely. But there are many more ways to solve most problems.
*/


// this file is for showing the most common data types and how to declare variables and assign a value to it.
// type varName = value;

void myFunction(){
    cout << "I'm a function with an empty output type." << endl;
}



int main(){

    cout << "Hello World\n";




    myFunction();

    bool myBool = false;
    cout << myBool << endl << '\n';


    int myPosNegInteger = -32768; //lowest number for signed ints
    cout << myPosNegInteger << endl << '\n';

    unsigned int myPosOnlyInteger = 65535; // highest positive number for ints
    cout << myPosOnlyInteger << endl << '\n';

    long myHugeInt = 2147483647; // largest number for longs
    cout << myHugeInt << endl << '\n';


    cout << setprecision(16);

    float myDecimalPoint = 3.141592654;  //data type only accurate for 6 sigfig
    cout << myDecimalPoint << endl << '\n';

    double myPreciseDecPoint = 3.141592654; // accurate for up to 12-13 sigfig.
    cout << myPreciseDecPoint << endl << '\n';


    // visit this link:     goo.gl/UJfC64
    // this link shows the representation of letters using 8 bits or 1 byte
    char myLetter = 'A';
    cout << myLetter << endl << '\n';

    // controlling the format of printed data with printf    goo.gl/qKU40
    printf("%c\n", myLetter); // represent as a letter
    printf("%d\n", myLetter);
    printf("%#x\n", myLetter);

    char myCString[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};  // an array, or list of letters.
    cout << myCString << endl << '\n';

    char myEmptyCString[13]; // an empty array
    // char myOtherCString = "Hello World"; valid in arduino but not here on desktop.
    cout << myEmptyCString << endl << '\n';

    string myHugeString = "Hello World";
    cout << myHugeString << endl << '\n';



    cout << "These are generally the data types available for you to use.\n\nYou will have to choose what data type to use based on what you need that information to do.\n\nIf you need a small whole number, ints are fine. If you need whole numbers larger than 65535, you'll need to use a long because it's capable of larger numbers.\n\nIf you need normal decimal point numbers only up to 6 sigfig(most of the time), you can just choose floats.\n\nPersonally I usually only deal in bool, int, float, and c-string on arduino.\n\nI usually only have to get more exotic if my problem I'm solving might specifically call for that.\n\nOne common instance I will use more exotic types is timekeepping. Arduino has a function called millis() which outputs the number of milliseconds the current program is run. Programs can run for upward of an hour for an average flight, so I know the number is huge, so I use the larges whole number type, unsigned long.";

    return 0;
}
