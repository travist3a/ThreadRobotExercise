#ifndef ROBOT_H
#define ROBOT_H
#include <iostream>
class Robot {
public:
	~Robot();
	int TruckID;
	int RobotID;


	void CreateThread();
	void Attach();
};
#endif