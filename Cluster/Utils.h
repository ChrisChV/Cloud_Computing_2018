#ifndef UTILS_H
#define UTILS_H

#include <iostream>

//Constantes de estado
#define ERROR -1
#define SUCCESS 1

using namespace std;

typedef string Command;
typedef int Status;
    
//Comandos
const Command OS_SSHPASS = "sshpass -p "; //Con password
const Command OS_SSH = "ssh ";
const Command OS_SCP = "scp ";
const Command OS_RM = "rm -f ";
const Command OS_AT = "@";
const Command OS_DIR_SLASH = "/";
const Command OS_HOME_DIR = "/home/";
const Command OS_HADOOP_USER = "hadoop/";
const Command OS_HADOOP_DIR = "hadoop/";
const Command OS_HADOOP_SBIN_DIR = "sbin/";
const Command OS_HADOOP_START_ALL_SCRIPT = "start-all.sh";



int runCommand(Command command){
    return system(command.c_str());
}

#endif