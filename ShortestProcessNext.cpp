/* 
 * File:   ShortestProcessNext.cpp
 * Author: Grant Kochmann and Maxwell Evans
 * 
     * Created on February 10, 2018, 2:12 PM
 */

#include "ShortestProcessNext.h"
using namespace std;
/*
output is:
current simulation time, process name or <idle>, length of interval, status code
"B" for blocked, "S" for time slice ended, "T" if the process terminated, or "I" for an idle interval.
 */
ShortestProcessNext::ShortestProcessNext(vector<string> names, vector<int> arrival_times, vector<int> total_times, vector<int> block_intervals) {
    simulationTime = 0;
    this->names = names;
    this->arrival_times = arrival_times;
    this->total_times = total_times;
    this->block_intervals = block_intervals;
}

void ShortestProcessNext::Execute() {
    //Adds processes to processes struct  
    for(int i = 0; i < names.size(); i++){ //Adding all of the processes to queue
        ShortestProcessNext::process p;
        p.name = names[i];
        p.arrival_time = arrival_times[i];
        p.block_interval = block_intervals[i];
        p.total_time = total_times[i];
        processes.push(p);
    }
    
    bool loop = true;
    while(loop){
        ShortestProcessNext::process tempProcess = processes.top();
        std::cout << simulationTime << "\t";
        simulationTime += tempProcess.block_interval;
    }
    
}




 