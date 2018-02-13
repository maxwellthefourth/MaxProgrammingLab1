/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Scheduler.h
 * Author: grant
 *
 * Created on February 12, 2018, 8:16 PM
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

using namespace std;
#include <iostream>
#include <vector>
#include <queue>

struct Process {
        string name;
        int arrival_time;
        int total_time;
        int block_interval;
        int processed_time;
        bool blocked;
        int block_time;
        
        //Implementing less than operator to be able to create priority queue of process struct
        //Based off of https://stackoverflow.com/questions/15601973/stl-priority-queue-of-c-with-struct
        bool operator<(const Process& temp) const
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
        
        Process& operator=(const Process& orig)
        {
            name = orig.name;
            arrival_time = orig.arrival_time;
            total_time = orig.total_time;
            block_interval = orig.block_interval;
        }
    };

class Scheduler {
public:
    Scheduler(vector<string> names, vector<int> arrival_times, vector<int> total_times, vector<int> block_intervals);
    ~Scheduler() { };
    
    Scheduler(const Scheduler& orig) = delete; // Class does not allow copy/move constructors/assignments
    Scheduler(Scheduler&& other) = delete;
    Scheduler& operator=(const Scheduler& orig) = delete;
    Scheduler& operator=(Scheduler&& orig) = delete;
    
    void ShortestProcessNext(int block_duration_arg);
    void RoundRobin(int block_duration_arg, int time_slice_arg);
    bool UpdateBlocked(std::priority_queue<Process> processes, int removed, bool testingAllBlocked);
private:
    int simulationTime;
    
    vector<string> names;
    vector<int> arrival_times;
    vector<int> total_times;
    vector<int> block_intervals;
};

#endif /* SCHEDULER_H */

