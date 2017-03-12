#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

string gpsTag = "$GPGGA,";
string inputFileName = "srcFile.txt";
string outputFileName = "processedGpsData.txt";

int main(){

    ifstream inputFile(inputFileName.c_str());
    if(!inputFile){
        cout << "input file failed to open" << '\n';
        exit(-1);
    }
    ofstream outputFile(outputFileName.c_str());
    if(!outputFile){
        cout << "output file failed to open" << '\n';
        exit(-1);
    }


    string line;
	while(!inputFile.eof()){
		getline(inputFile, line);
        if(line.substr(0, gpsTag.size()) == gpsTag){
            outputFile << line.substr(gpsTag.size(), line.size() - 1) << endl; // write to output file
        }
		line.clear();//empty line to clean up for next run
	}


    inputFile.close();
    return 0;
}
