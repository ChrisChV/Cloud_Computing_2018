#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <iostream>
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
    private:
        Hosts * hosts;
};

void MessageManager::setHosts(Hosts * hosts){
    this->hosts = hosts;
}

Status MessageManager::sendFile(string fileName, string hostName){
    HostThings host;
    if(hosts->findByName(hostName, host) == false) return ERROR;
    Command command = OS_SSHPASS + "'" + host.password + "' " + OS_SCP + fileName + " " + 
                        host.user_name + OS_AT + host.ip + ":" + OS_HOME_DIR + host.user_name + OS_DIR_SLASH;
    cout<<command<<endl;
    runCommand(command);
    return SUCCESS;
}

#endif