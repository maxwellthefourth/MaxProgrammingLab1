/* 
 * File:   RoundRobin.cpp
 * Author: Grant Kochmann and Maxwell Evans
 * 
 * Created on February 10, 2018, 2:04 PM
 */

#include "RoundRobin.h"

RoundRobin::RoundRobin(vector<string> names, vector<int> arrival_times, vector<int> total_times, vector<int> block_intervals, int block_duration, int time_slice) {
    simulationTime = 0;
    this->names = names;
    this->arrival_times = arrival_times;
    this->total_times = total_times;
    this->block_intervals = block_intervals;
    int temp = block_intervals.size();
    for (int i = 0; i < temp; i++)
        block_intervals[temp+i] = block_intervals[i];
    this->block_duration = block_duration;
    this->time_slice = time_slice;
}

void RoundRobin::Execute() {
    int tempCompare = updateTempCompare();
    vector<int> blockDurationCheck;
    
    //temp stuff, please fix
    int currentTime = simulationTime; // Set first default time
    string currentName = names[tempCompare]; // Set first default name
    int length = time_slice; // Set first default length
    string status = "B"; // Set first default status
    if (length < total_times[tempCompare]) { // Check if length is less than overall total time for process. If it is, updates length and status
        length = total_times[tempCompare];
        status = "T";
    }
    
    bool loop = true;
    while (loop) {
        if (time_slice < block_intervals[tempCompare]) {
            length = time_slice;
            status = "S";
        }
        else if (time_slice > block_intervals[tempCompare]) {
            length = time_slice - block_intervals[tempCompare];
            status = "B";
        }
        block_intervals[tempCompare] -= length; // Subtract from block-interval to know when to set status to block
        total_times[tempCompare] -= length;
        
        if (block_intervals[tempCompare] = 0) {
            block_intervals[tempCompare] = block_intervals[block_intervals.size()/2+tempCompare];
            blockDurationCheck.push_back(tempCompare);
        }
        
        if (total_times[tempCompare] = 0) {
            status = "T";
            names.erase(names.begin()+tempCompare);
            arrival_times.erase(arrival_times.begin()+tempCompare);
            total_times.erase(total_times.begin()+tempCompare);
            block_intervals.erase(block_intervals.begin()+tempCompare);
        }
        
        cout << " " << currentTime << "\t" << currentName << "\t" << length << "\t" << status << "\t" << endl;
        currentTime += length;
        tempCompare = updateTempCompare();
    }
}

int RoundRobin::updateTempCompare() {
    int sizeComparison = 0;
    for (int i = 0; i < arrival_times.size(); i++) {
        if (arrival_times[i] < arrival_times[sizeComparison]) {
            sizeComparison = i;
        }
    }
    return sizeComparison;
}
