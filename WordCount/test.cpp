#include <iostream>
#include <chrono>
#include "send.h"
#include "split.h"

using namespace std;

string getNowTime(){
	auto nowTimeClock = chrono::system_clock::now();
	time_t nowTime_t = chrono::system_clock::to_time_t(nowTimeClock);
	string nowTime(ctime(&nowTime_t));
	nowTime.pop_back();
	return nowTime;
}

int main(){
	cout<<getNowTime()<<endl;
	splitFilev2("OutFile2G", 11);
	cout<<getNowTime()<<endl;
}