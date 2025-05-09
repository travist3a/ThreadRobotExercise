#include "robot.h"
#include <iostream>
#include <thread>
#include <vector>
#include <future>

void work(int numtrucks, int numrobots);
void ConcurrentThreads(int numRobots, int numTrucks);
void AsyncThreads(int numRobots, int numTrucks);
std::string AsyncThreadHelper(int truck, int robot);
std::string AsyncThreadHelperRoomba(int truck, int robot, int truck2);
void AsyncThreadsRoomba(int numRobots, int numTrucks);

int main()
{
    //ConcurrentThreads(4, 5);
    work(4, 5);
    //Roomba Room(1,2,3);
}

void work(int numtrucks, int numrobots) {

    //ConcurrentThreads(numrobots, numtrucks);
    AsyncThreadsRoomba(numrobots, numtrucks);
}


void createRobot(int truck, int robotId) {

}
void ConcurrentThreads(int numRobots, int numTrucks) {
    std::vector<std::thread> threads;
    std::vector<std::future<std::string>> futures;
    
    auto lambdaex = [](int truck, int robotId, std::promise<std::string>&& promise){ //&& Rvalue = temporary object
        Robot currRobot(robotId, truck);
        
        promise.set_value(currRobot.Attach());
        };

    for (int j = 0; j < numTrucks; j++) {
        for (int i = 0; i < numRobots; i++) {
            std::promise<std::string> promise;
            futures.emplace_back(promise.get_future());
            threads.emplace_back(std::thread(lambdaex, j, i, std::move(promise))); //Need std::move to turn promise into rValue
        }
    }
    for (auto& x : futures) { //For each loop to loop through every thread and return all at once
        std::cout << x.get() << std::endl;
    }
    for (auto& x : threads) {
        x.join();
    }
}


void AsyncThreads(int numRobots, int numTrucks) {
    std::vector<std::future<std::string>> futures;

    // Each (robot, truck) combination gets a separate async task
    for (int truck = 0; truck < numTrucks; ++truck) {
        for (int robot = 0; robot < numRobots; ++robot) {
            futures.emplace_back(std::async(std::launch::async, AsyncThreadHelper,truck,robot));                                                                 ///
        }
    }

    
    for (auto& fut : futures) {  // Waits until future is ready in each instance
        std::cout << fut.get() << std::endl;
    }
}

std::string AsyncThreadHelper(int truck, int robot)
{
    Robot currRobot(robot + 1, truck + 1);
    return currRobot.Attach();
}

void AsyncThreadsRoomba(int numRobots, int numTrucks) {
    std::vector<std::unique_ptr<std::mutex>> mtxs(numTrucks);
    std::vector<int> timescleaned (numTrucks);
    std::vector<std::future<std::string>> futures;
    for (auto& mtx: mtxs) {
        mtx = std::make_unique<std::mutex>();
        timescleaned.emplace_back(0);
    }
    auto updateMtx = [&mtxs, &timescleaned](int truck) {
        std::lock_guard<std::mutex> lock(*mtxs.at(truck));
        timescleaned.at(truck)++;
        }
    // Each (roomba, truck) combination gets a separate async task
    for (int truck = 0; truck < numTrucks; truck+=2) {
        for (int robot = 0; robot < numRobots; ++robot) {
            futures.emplace_back(std::async(std::launch::async, AsyncThreadHelperRoomba, truck, robot, truck+1));                                                                 ///
        }
    }


    for (auto& fut : futures) {  // Waits until future is ready in each instance
        std::cout << fut.get() << std::endl;
    }
}

std::string AsyncThreadHelperRoomba(int truck, int robot, int truck2)
{
    Roomba currRobot(robot + 1, truck + 1, truck2 +1);
    return currRobot.Attach();
}