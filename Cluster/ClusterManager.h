#ifndef CLUSTERMANAGER_H
#define CLUSTERMANAGER_H

#include <iostream>
#include "MessageManager.h"
#include "Utils.h"

using namespace std;

class ClusterManager{
    public:
        ClusterManager(){}
        ClusterManager(string fileName);
        void init(string fileName);
        void startHadoopCluster();
    private:
        Hosts hosts;
        MessageManager msgManager;
};

ClusterManager::ClusterManager(string fileName){
    init(fileName);
}

void ClusterManager::init(string fileName){
    hosts = Hosts(fileName);
    msgManager = MessageManager(&hosts);
}

void ClusterManager::startHadoopCluster(){
    Command command = OS_HOME_DIR + OS_HADOOP_USER + OS_HADOOP_DIR + OS_HADOOP_SBIN_DIR + OS_HADOOP_START_ALL_SCRIPT;
    msgManager.runSSHCommandToAll(command);
}

#endif