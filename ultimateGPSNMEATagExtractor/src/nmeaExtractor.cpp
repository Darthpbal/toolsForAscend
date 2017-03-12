#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

int main(){

    ifstream inputFile("srcFile");
    if(!inputFile){
        cout << "input file failed to open" << '\n';
        exit(-1);
    }


    string line;
	string processedLine;
	while(!inputFile.eof()){
		getline(inputFile, line);
		processedLine = extractFromLine(line, colArrSize, colArray);
		outputFile << processedLine; // write to output file
		line.clear();//empty line to clean up for next run
	}


    inputFile.close();
    return 0;
}
