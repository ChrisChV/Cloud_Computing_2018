#ifndef UTILS_H
#define UTILS_H

#include <iostream>

using namespace std;

typedef string Command;
    
//Comandos
const Command OS_SSHPASS = "sshpass -p "; //Con password
const Command OS_SSH = "ssh ";
const Command OS_SCP = "scp ";
const Command OS_AT = "@";
const Command OS_DIR_SLASH = "/";


int runCommand(Command command){
    return system(command.c_str());
}

#endif