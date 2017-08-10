#include <iostream>
#include <string>
using namespace std;

int promptInt(string prompt){
    cout << prompt << endl;
    int response;
    cin >> response;
    return response;
}



bool checkIfEven(int num){
    int leftover = num % 2;

    if(leftover == 0){
        return true;
    }

    else{
        return false;
    }
}






int main(){
    cout << "Hello World\n";

    // this portion is for showing if checks with their conditions.
    int numberToCheck = 2;

    cout << "number = " << numberToCheck << endl;

    cout << "number is ";
    if (numberToCheck > 5) {
        cout << "greater";
    }
    else{
        cout << "less";
    }
    cout << " than five\n";




    // (starting point; condition; increment)
    int squareSize = 20;
    char squareContent = '=';
    for(int i = 0; i < squareSize; i++){
        for(int j = 0; j < squareSize; j++){
            cout << squareContent << ' ';
        }
        cout << endl;
        // cout << '\n'; // either one works, endl is the same as newline.
    }



    int usrNumber;

    do {
        usrNumber = promptInt("gimme a number");
    } while(checkIfEven(usrNumber));



    usrNumber = promptInt("trying again with just a while loop... gimme numberrr");

    while (! checkIfEven(usrNumber)) {
        usrNumber = promptInt("trying again with just a while loop... gimme numberrr");
    }

    return 0;
}
