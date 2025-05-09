#ifndef ROBOT_H
#define ROBOT_H
#include <iostream>
class Machine {
public:
	Machine();
	~Machine();

	virtual std::string process() const;
};
class Robot : public Machine {
public:
	Robot();
	~Robot();
	int TruckID;
	int RobotID;
	Robot(int robotId, int truckId);

	void CreateSyncThread();
    std::string process();
	std::string Attach();
};

class Roomba : public Robot {
public:
	Roomba();
	Roomba(int robotId, int truckId, int truck2ID);
	~Roomba();
	std::string Attach();
	int Truck2ID;
};
#endif