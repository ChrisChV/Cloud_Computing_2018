#ifndef SPLIT_H
#define SPLIT_H

#include <iostream>

using namespace std;

typedef long StoreType;

void splitFile(string fileName, int splits){
	string command = "split -l$((`wc -l < "+  fileName +" `/" + to_string(splits) +")) "+ fileName  + " " + fileName + " -da 4";
	system(command.c_str());
}

StoreType getSizeOfFile(string fileName){
	string tempFileName = ".tempSize";
	string command = "ls -l OutFile | awk '{print $5}' > " + tempFileName;
	system(command.c_str());
	ifstream tempFile(tempFileName);
	string s_size = "";
	tempFile>>s_size;
	StoreType res_size = stoi(s_size);
	tempFile.close();
	string rmCommand = "rm " + tempFileName;
	system(rmCommand.c_str());
	return res_size;
}


#endif