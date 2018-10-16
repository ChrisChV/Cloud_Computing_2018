#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <iostream>
#include <fstream>
#include "Hosts.h"
#include "Utils.h"

using namespace std;

class MessageManager{
    public:
        MessageManager(){
            this->hosts = nullptr;
        }
        MessageManager(Hosts * hosts){
            setHosts(hosts);
        }

        void setHosts(Hosts * hosts);
        
        Status sendFile(string fileName, string hostName);
        Status runSSHCommandToAll(Command command);
        Status runSSHCommand(Command command, string hostName);
        Status ping(string ip);
    private:
        Hosts * hosts;
        Command makeSSHCommand(Command command, HostThings host);
};

void MessageManager::setHosts(Hosts * hosts){
    this->hosts = hosts;
}

Command MessageManager::makeSSHCommand(Command command, HostThings host){
    Command newCommand = OS_SSHPASS + "'" + host.password + "' " + OS_SSH + 
                            host.user_name + OS_AT + host.ip + " \"" + command + "\"";
    return newCommand;
}

Status MessageManager::ping(string ip){
    string tempFile = ".tempPingFile";
    Command command = "if ping -c1 " + ip + " > /dev/null 2> /dev/null ; then echo " + to_string(SUCCESS) + " > " + 
                            tempFile + "; else echo " + to_string(ERROR) + " > " + tempFile + "; fi";
    runCommand(command);
    ifstream file(tempFile);
    string res = "";
    file >> res;
    file.close();
    command = OS_RM + tempFile;
    runCommand(command);
    return stoi(res);
}

Status MessageManager::sendFile(string fileName, string hostName){
    HostThings host;
    if(hosts == nullptr or hosts->findByName(hostName, host) == false) return ERROR;
    Command command = OS_SSHPASS + "'" + host.password + "' " + OS_SCP + fileName + " " + 
                        host.user_name + OS_AT + host.ip + ":" + OS_HOME_DIR + host.user_name + OS_DIR_SLASH;
    cout<<command<<endl;
    runCommand(command);
    return SUCCESS;
}

Status MessageManager::runSSHCommandToAll(Command command){
    if(hosts == nullptr) return ERROR;
    Command newCommand = "";
    for(auto iter = hosts->begin(); iter != hosts->end(); ++iter){
        newCommand = makeSSHCommand(command, iter->second);
        cout<<"Iniciando "<<iter->second.name<<endl;;
        if(ping(iter->second.ip) == ERROR){
            cout<<"Nodo "<<iter->second.name<<" sin conección"<<endl;
            continue;
        }
        cout<<newCommand<<endl;
        runCommand(newCommand);
    }
    return SUCCESS;
}

Status MessageManager::runSSHCommand(Command command, string hostName){
    HostThings host;
    if(hosts == nullptr or hosts->findByName(hostName, host) == false) return ERROR;
    Command newCommand = makeSSHCommand(command, host);
    cout<<newCommand<<endl;
    runCommand(newCommand);
    return SUCCESS;
}

#endif