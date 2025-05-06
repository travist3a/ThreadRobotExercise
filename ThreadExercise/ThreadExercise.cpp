#include "robot.h"
#include <iostream>
#include <thread>
#include <vector>

void work(int numtrucks, int numrobots);

int main()
{
    
    work(4, 5);
}

void work(int numtrucks, int numrobots) {
    std::vector<Robot> robots(numrobots);

    for (int i = 0; i < numrobots; ++i)
    {
        robots[i].RobotID = i+1;
    }

    for (int i = 0; i < numtrucks; ++i)
    {
        for(int j=0;j<numrobots;j++)
        {
            robots[j].TruckID = i+1;
            robots[j].CreateThread();
        }
    }
}

