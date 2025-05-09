#include "robot.h"
#include <iostream>
#include <thread>
#include <string>

Machine::Machine()
{
}

Machine::~Machine()
{
}

std::string Machine::process() const
{
	return std::string();
}

Robot::Robot(int robotId, int truckId)
{
	RobotID = robotId;
	TruckID = truckId;
}

void Robot::CreateSyncThread() {
	std::thread Process(&Robot::Attach, this);
	Process.join();
	return;
}

std::string Robot::process()
{
	return Attach();
}



std::string Robot::Attach(){
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	//std::cout << "Robot " + std::to_string(Robot::RobotID) + " attaching door to truck " + std::to_string(Robot::TruckID) << std::endl;
	return "Future Robot " +  std::to_string(Robot::RobotID) + " attaching door to truck " + std::to_string(Robot::TruckID);
}

Robot::Robot()
{
	RobotID = -1;
	TruckID = -1;
	std::cout << "Robot Initialized" << std::endl;
}

Robot::~Robot()
{
	std::cout << "Robot Kill!" << std::endl;
	//std::cout << "Robot " << RobotID << " deconstructed and out of scope" << std::endl << std::endl;
}


Roomba::Roomba()
{

	Truck2ID = -1;

}

Roomba::Roomba(int robotId, int truckId, int truck2ID)
{
	RobotID = robotId;
	TruckID = truckId;
	Truck2ID = truck2ID;
}

Roomba::~Roomba()
{
	std::cout << "Roomba Kill!"<<std::endl;

}
std::string Roomba::Attach()
{
	return "Future Roomba " + std::to_string(Roomba::RobotID) + " cleaning truck " + std::to_string(Roomba::TruckID) + "\n" + "Future Roomba " + std::to_string(Roomba::RobotID) + " cleaning truck " + std::to_string(Roomba::Truck2ID) + "\n";
}
