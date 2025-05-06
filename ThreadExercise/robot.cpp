#include "robot.h"
#include <iostream>
#include <thread>


void Robot::CreateThread() {
	std::thread Process(&Robot::Attach, this);
	Process.join();
	return;
}

void Robot::Attach() {
	std::cout <<"Robot " << Robot::RobotID << " attaching door to truck " <<TruckID<< std::endl;
	return;
}

Robot::~Robot()
{
	std::cout << "Robot " << RobotID << " deconstructed and out of scope" << std::endl;
}