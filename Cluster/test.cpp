#include <iostream>
#include "ClusterManager.h"

using namespace std;

int main(){
    ClusterManager cManager("hosts");
    cManager.startHadoopCluster();
}