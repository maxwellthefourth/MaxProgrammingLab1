/* 
 * File:   ShortestProcessNext.h
 * Author: Grant Kochmann and Maxwell Evans
 *
 * Created on February 10, 2018, 2:12 PM
 */

#ifndef SHORTESTPROCESSNEXT_H
#define SHORTESTPROCESSNEXT_H

using namespace std;
#include <iostream>
#include <vector>
#include <queue>

class ShortestProcessNext {
public:
    ShortestProcessNext(vector<string> names, vector<int> arrival_times, vector<int> total_times, vector<int> block_intervals);
    ~ShortestProcessNext() {
        
    };
    ShortestProcessNext(const ShortestProcessNext& orig) = delete; // Class does not allow copy/move constructors/assignments
    ShortestProcessNext(ShortestProcessNext&& other) = delete;
    ShortestProcessNext& operator=(const ShortestProcessNext& orig) = delete;
    ShortestProcessNext& operator=(ShortestProcessNext&& orig) = delete;
    
    void Execute();
    int FindShortestProcess();
private:
    int simulationTime;
    struct process {
        string name;
        int arrival_time;
        int total_time;
        int block_interval;
        
        //Implementing less than operator to be able to create priority queue of process struct
        //Based off of https://stackoverflow.com/questions/15601973/stl-priority-queue-of-c-with-struct
        bool operator<(const process& temp) const
        {
            //I have reversed the operator inside this function so that it
            //actually creates a priority_queue with the smallest element on
            //top instead of the largest
            if (block_interval > total_time){
                return block_interval > temp.block_interval;
            } else {
                return total_time > temp.total_time;
            }          
        }
        
        process& operator=(const process& orig)
        {
            name = orig.name;
            arrival_time = orig.arrival_time;
            total_time = orig.total_time;
            block_interval = orig.block_interval;
        }
    };
    
    vector<string> names;
    vector<int> arrival_times;
    vector<int> total_times;
    vector<int> block_intervals;
    
    std::priority_queue<process> processes;
};

#endif /* SHORTESTPROCESSNEXT_H */

