/*
this program is now unchanged from last known working form. It's used for parsing
data from the text file while the gps was fixed and while it wasn't assumine the
files are only all location fixed data or only all unfixed data. So the data should
be sorted by these categories first.



headers while not fixed 3
Date
Sats
Time

**proper format
Date,Sats,Time,



headers while fixed 9
Date
Sats
Coords
Google Map Coords
Quality
Pressure
Alt
Delay
Time

**proper format
Date,Sats,Coords,Google Map Coords,Quality,Pressure,Alt,Delay,Time\n


timestamps in data imply that GPS aquired location at 843am
and held location for 1 hour 29 min and 52 sec
and stopped logging at timestamp 10:13am 24 sec
*/


#include <iostream>//terminal screen access
#include <fstream>//text file access
#include <cstdlib>//for the exit function
using namespace std;

int main(){
    //check if anyone's there
    cout << "Hello World\n";

    //open the text file for reading and then checking to make sure it opened properly.
    ifstream dirtyFile("fixedGps.txt");//inputFileStream type variable name dirtyFile and the actual text filename is the argument
    if (!dirtyFile) {//if not opened properly
        cout << "unable to open file for reading... terminating...\n";
        exit(-1);//exit program with error code -1
    }
    else{
        cout << "file opened successfully\n";
    }


    //open text file for writing to and check to make sure it opened
    ofstream cleanFile("cleanFixedGps.txt");
    if (!cleanFile) {
        cout << "unable to open file for writing" << endl;
        exit(-1);
    }
    else{
        cout << "file opened successfully\n";
    }


    string rawLine, cleanLine;
    while(!dirtyFile.eof()){
        getline(dirtyFile, rawLine);
        if(rawLine.substr(0, rawLine.size() - 1) == "19/11/2016"){
            cleanLine += rawLine.substr(0, rawLine.size() - 1) + ",";
            for (int i = 0; i < 8; i++) {
                getline(dirtyFile, rawLine);
                cleanLine += rawLine.substr(0, rawLine.size() - 1) + ",";
            }
            cleanFile << cleanLine.substr(0, cleanLine.size() - 1) << endl;
            cleanLine.clear();
        }
    }


    dirtyFile.close();//close the files
    cleanFile.close();
    return 0;
}





/*

19/11/2016
10
3243.0915N, 11156.0615W
32.7182, -111.9344
0.15
74.83
0.00
0
15:43:39.0

*/





// // working other versions. This gets 9 lines, the other if checks are for arbitrarily getting any max lines.

//scalable for 3 datapoints or 9
// int lineCount = 0, lineMax;
// cout << "How many columns? ";//prompt user
// cin >> lineMax;//get input
//
//
// string rawLine, cleanLine;
// while(!dirtyFile.eof()){//while not at the end of the file
//     getline(dirtyFile, rawLine);//getline from dirtyFile and put in rawLine
//     lineCount++;//count up lineCount
//     if(lineCount < lineMax){//if max not reached
//         cleanLine += rawLine.substr(0, rawLine.size() - 1) + ",";//add this line to the bulk line and add a comma
//     }
//     else{
//         cleanLine += rawLine.substr(0, rawLine.size() - 1);//these needed to be substrings because theres a return character in there thats messing things up... stupid windows...
//         cleanFile << cleanLine << endl;
//         cleanLine.clear();//reset variable so when loop starts again and stuff gets stored again, the old clean line isn't there anymore
//         lineCount = 0;//reset the line count
//     }
// }



//for 9 columns
// string rawLine, cleanLine;
// while (!dirtyFile.eof()) {
//     getline(dirtyFile, rawLine);
//     cleanLine += rawLine.substr(0, rawLine.size() - 1) + ",";
//     getline(dirtyFile, rawLine);
//     cleanLine += rawLine.substr(0, rawLine.size() - 1) + ",";
//     getline(dirtyFile, rawLine);
//     cleanLine += rawLine.substr(0, rawLine.size() - 1) + ",";
//     getline(dirtyFile, rawLine);
//     cleanLine += rawLine.substr(0, rawLine.size() - 1) + ",";
//     getline(dirtyFile, rawLine);
//     cleanLine += rawLine.substr(0, rawLine.size() - 1) + ",";
//     getline(dirtyFile, rawLine);
//     cleanLine += rawLine.substr(0, rawLine.size() - 1) + ",";
//     getline(dirtyFile, rawLine);
//     cleanLine += rawLine.substr(0, rawLine.size() - 1) + ",";
//     getline(dirtyFile, rawLine);
//     cleanLine += rawLine.substr(0, rawLine.size() - 1) + ",";
//     getline(dirtyFile, rawLine);
//     cleanLine += rawLine.substr(0, rawLine.size() - 1);
//     cout << cleanLine << endl;
//     cleanLine.clear();
// }








////working other version. This gets 3 lines, the other if checks are for arbitrarily getting any max lines.
// string rawLine, cleanLine;
// while (!dirtyFile.eof()) {
//     getline(dirtyFile, rawLine);
//     cleanLine += rawLine.substr(0, rawLine.size() - 1) + ",";
//     getline(dirtyFile, rawLine);
//     cleanLine += rawLine.substr(0, rawLine.size() - 1) + ",";
//     getline(dirtyFile, rawLine);
//     cleanLine += rawLine.substr(0, rawLine.size() - 1);
//     cout << cleanLine << endl;
//     cleanLine.clear();
// }
