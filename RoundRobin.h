///* 
// * File:   RoundRobin.h
// * Author: Grant Kochmann and Maxwell Evans
// *
// * Created on February 10, 2018, 2:03 PM
// */
//
//#ifndef ROUNDROBIN_H
//#define ROUNDROBIN_H
//
//using namespace std;
//#include <iostream>
//#include <vector>
//
//class RoundRobin {
//public:
//    RoundRobin(vector<string> names, vector<int> arrival_times, vector<int> total_times, vector<int> block_intervals, int block_duration, int time_slice);
//    ~RoundRobin() {
//        
//    };
//    RoundRobin(const RoundRobin& orig) = delete; // Class does not allow copy/move constructors/assignments
//    RoundRobin(RoundRobin&& other) = delete;
//    RoundRobin& operator=(const RoundRobin& orig) = delete;
//    RoundRobin& operator=(RoundRobin&& orig) = delete;
//    
//    void Execute();
//private:
//    int updateTempCompare();
//    int simulationTime;
//    vector<string> names;
//    vector<int> arrival_times;
//    vector<int> total_times;
//    vector<int> block_intervals;
//    
//    int block_duration;
//    int time_slice;
//};
//
//#endif /* ROUNDROBIN_H */
//
