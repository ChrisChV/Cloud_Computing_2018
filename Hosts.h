#ifndef HOSTS_H
#define HOSTS_H

#include <iostream>
#include <fstream>
#include <map>
#include <tuple>

#define LINE_ON_FILE_ERROR 1

using namespace std;

/*
    Format of the hosts file:
    <name> <ip> <user-name> <password>
*/

class HostThings{
    public:
        HostThings(){
            name = "";
            ip = "";
            user_name = "";
            password = "";
        }
        HostThings(string name, string ip, string user_name, string password){
            this->name = name;
            this->ip = ip;
            this->user_name = user_name;
            this->password = password;
        }
        HostThings(string ip, string user_name, string password){
            this->ip = ip;
            this->user_name = user_name;
            this->password = password;
        }
        void print(){
            cout<<"=============="<<endl;
            cout<<"Name: "<<name<<endl;
            cout<<"Ip: "<<ip<<endl;
            cout<<"User Name: "<<user_name<<endl;
            cout<<"Password: "<<password<<endl;
            cout<<"=============="<<endl<<endl;
        }
        string name;
        string ip;
        string user_name;
        string password;
};

class Hosts{
    public:
        Hosts(){}
        Hosts(string fileName);
        void open(string fileName);
        void print();
        bool findByName(string name, HostThings & res);
        bool findByIp(string ip, HostThings & res);
        
    private:
        map<string, HostThings> hostMap;
        HostThings getLine(ifstream & file);
};

Hosts::Hosts(string fileName){
    open(fileName);
}

void Hosts::open(string fileName){
    hostMap.clear();
    ifstream file(fileName);
    string name = "";
    HostThings things;
    map<string, HostThings>::iterator findRes;
    while(file >> name){
        things = getLine(file);
        things.name = name;
        findRes = hostMap.find(name);
        if(findRes != hostMap.end()){
            cout<<"Host repetido: "<<name<<endl;            
            findRes->second = things;
        } 
        else hostMap[name] = things;
    }
    file.close();
}

bool Hosts::findByName(string name, HostThings & res){
    auto findRes = hostMap.find(name);
    if(findRes == hostMap.end()) return false;
    res = findRes->second;
    return true;
}

bool Hosts::findByIp(string ip, HostThings & res){
    for(auto iter = hostMap.begin(); iter != hostMap.end(); ++iter){
        if(iter->second.ip == ip){
            res = iter->second;
            return true;
        }
    }
    return false;
}

HostThings Hosts::getLine(ifstream & file){
    string ip = "";
    string user_name = "";
    string password = "";
    file>>ip;
    file>>user_name;
    file>>password;
    //if(!file >> ip) throw(LINE_ON_FILE_ERROR);
    //if(!file >> user_name) throw(LINE_ON_FILE_ERROR);
    //if(!file >> password) throw(LINE_ON_FILE_ERROR);
    return HostThings(ip, user_name, password);
}

void Hosts::print(){
    for(auto iter = hostMap.begin(); iter != hostMap.end(); ++iter){
        iter->second.print();
    }
}

#endif