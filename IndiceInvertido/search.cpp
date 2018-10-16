#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// hdfs dfs -cat miniGoogleOut/part* | grep make > tt

const string DIR_TO_PUT_DATA = "/tmp/";
const string TEMP_SEARCH_FILE_NAME = DIR_TO_PUT_DATA + ".tempSearch";
const string TEMP_RES_FILE_NAME = DIR_TO_PUT_DATA + "resSearch";
const string INVERTED_INDEX_HDFS_FILE_PATH = "miniGoogleData/part*";
const string URLS_DATA_FILE_PATH = "/home/hadoop/Preprocessing/urls.data";

string getFileName(string hdfsFile){
    string actualName = "";
    for(char c : hdfsFile){
        if(c == '/'){
            actualName.clear();
            continue;
        }
        actualName.push_back(c);
    }
    return actualName;
}

int main(int argc, char ** argv){
    if(argc != 2){
        cout<<"Faltan argumentos <word to find>"<<endl;
        return 1;
    }
    string word(argv[1]);
    string command = "/opt/hadoop-2.7.3/bin/hdfs dfs -cat /usr/hadoop/" + INVERTED_INDEX_HDFS_FILE_PATH + " | grep -w " + word + " > " + TEMP_SEARCH_FILE_NAME;
    system(command.c_str());
    
    vector<string> pathToFiles;
    string tempWord = "";

    ifstream searchFile(TEMP_SEARCH_FILE_NAME);
    
    vector<string>::iterator tempFind;

    searchFile >> tempWord;
    while(searchFile >> tempWord){
        tempFind = find(pathToFiles.begin(), pathToFiles.end(), tempWord);
        if(tempFind == pathToFiles.end()){
            pathToFiles.push_back(tempWord);
        }
    }

    searchFile.close();

    string resTempPath = "";
    string tempName = "";

    command = "rm -f " + TEMP_RES_FILE_NAME;
    system(command.c_str());

    for(string s : pathToFiles){
        tempName = getFileName(s);
        command = "sed '" + tempName + "q;d' " + URLS_DATA_FILE_PATH + " >> " + TEMP_RES_FILE_NAME;
        system(command.c_str());

        /*
        resTempPath = DIR_TO_PUT_DATA + tempName;
        command = "hdfs dfs -get " + s + " " + DIR_TO_PUT_DATA;
        system(command.c_str());
        resFile<<resTempPath<<endl;
        cout<<s<<endl;
        cout<<tempName<<endl;
        */
    }
}
