/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Scheduler.cpp
 * Author: grant
 * 
 * Created on February 12, 2018, 8:16 PM
 */

#include "Scheduler.h"

Scheduler::Scheduler(vector<string> names, vector<int> arrival_times, vector<int> total_times, vector<int> block_intervals){
    this->names = names;
    this->arrival_times = arrival_times;
    this->total_times = total_times;
    this->block_intervals = block_intervals;
}

void Scheduler::ShortestProcessNext(int block_duration_arg) {
    simulationTime = 0;
    
    std::priority_queue<Process> processes;
    int block_duration = block_duration_arg;
    int current_time = 0;
    string current_name;
    string status;
    int length;
    
    //Adds processes to processes struct  
    //Adding Process A to queue because it arrives at time 0
    if(processes.size() == 0) {
        Process p;
        p.name = names[0];
        p.arrival_time = arrival_times[0];
        p.block_interval = block_intervals[0];
        p.total_time = total_times[0];
        p.processed_time = 0;
        p.block_time = 0;
        p.blocked = false;
        processes.push(p);
    }

    
    
    bool loop = true;
    while(loop){
        if(simulationTime > 100){
            loop = false;
        }
        Process tempProcess = processes.top();
        processes.pop();
        
        current_time = simulationTime;
        
        for(int i = 0; i < tempProcess.block_interval; i++){
            cout << i;
            tempProcess.processed_time++;
            simulationTime++;
            if(simulationTime == 1) { //Adding B at time 1
                Process p;
                p.name = names[1];
                p.arrival_time = arrival_times[1];
                p.block_interval = block_intervals[1];
                p.total_time = total_times[1];
                p.processed_time = 0;
                p.block_time = 0;
                p.blocked = false;
                processes.push(p);
            }
            if(simulationTime == 2) { //Adding C at time 1
                Process p;
                p.name = names[2];
                p.arrival_time = arrival_times[2];
                p.block_interval = block_intervals[2];
                p.total_time = total_times[2];
                p.processed_time = 0;
                p.block_time = 0;
                p.blocked = false;
                processes.push(p);
            }
        }
        //tempProcess.processed_time += tempProcess.block_interval;
        tempProcess.block_time = block_duration;
        tempProcess.blocked = true;
        
        status = "B";
        //UpdateBlocked(processes, tempProcess.block_interval, false);
                
        current_name = tempProcess.name;
        length = tempProcess.block_interval;
        
//        if(UpdateBlocked(processes, tempProcess.block_interval, true)){
//            current_name = "<idle>";
//            status = "S";
//        }
        
        simulationTime += tempProcess.block_interval;
        if(tempProcess.processed_time >= tempProcess.total_time){
            status = "T";
        } else {
            processes.push(tempProcess);
        }

        if (processes.size() == 0) {
            cout << " " << simulationTime << "\t" << "<done>" << "\t" << "turnaroundTime/initialSize" << "\t" << endl;
            loop = false;
        } else {
            cout << " " << current_time << "\t" << current_name << "\t" << length << "\t" << status << "\t" << endl;
        }
        
    }
}

bool Scheduler::UpdateBlocked(std::priority_queue<Process> processes, int removed, bool testingAllBlocked){
    Process p1 = processes.top();
    processes.pop();
    Process p2 = processes.top();
    processes.pop();
    Process p3 = processes.top();
    processes.pop();
    
    if(testingAllBlocked){
        if(p1.blocked && p2.blocked && p3.blocked){
            processes.push(p1);
            processes.push(p2);
            processes.push(p3);
            return true;
        } else {
            processes.push(p1);
            processes.push(p2);
            processes.push(p3);
            return false;
        }
    }
    
    p1.block_time -= removed;
    p2.block_time -= removed;
    p3.block_time -= removed;
    
    if(p1.block_time <= 0){
        p1.block_time = 0;
        p1.blocked = false;
    }
    if(p2.block_time <= 0){
        p2.block_time = 0;
        p2.blocked = false;
    }
    if(p3.block_time <= 0){
        p3.block_time = 0;
        p3.blocked = false;
    } 
    
    processes.push(p1);
    processes.push(p2);
    processes.push(p3);
    
    return false;
}

void Scheduler::RoundRobin(int block_duration_arg, int time_slice_arg) {
    for(int i = 0; i < names.size(); i++){ //Adding all of the processes to queue
        Process p;
        p.name = names[i];
        p.arrival_time = arrival_times[i];
        p.block_interval = block_intervals[i];
        p.total_time = total_times[i];
    }
    
    simulationTime = 0;
    
    int block_duration = block_duration_arg;
    int time_slice = time_slice_arg;
    
    int tempCompare = 0;
    int temp = block_intervals.size();
    block_intervals.resize(block_intervals.size()*2);
    for (int i = 0; i < temp; i++) {
        block_intervals[temp+i] = block_intervals[i];
    }
    
    int currentTime = simulationTime; // Initialize current time
    string currentName = names[0]; // Set first to default name
    int length = time_slice; // Initialize length
    string status = "temp"; // Initialize status
    vector<int> blockTimes(names.size(), 0); // Create a vector to see which are blocked
    double turnaroundTime = 0;
    int initialSize = names.size();
    
    bool loop = true;
    while (loop) {
        currentName = names[tempCompare];
        length = time_slice;
        
        // Remove process from queue once it finishes
        if (total_times[tempCompare] == 0) {
            turnaroundTime += currentTime;
            names.erase(names.begin()+tempCompare);
            arrival_times.erase(arrival_times.begin()+tempCompare);
            total_times.erase(total_times.begin()+tempCompare);
            block_intervals.erase(block_intervals.begin()+tempCompare);
            blockTimes.erase(blockTimes.begin()+tempCompare);
        }

        // check if blocked
        int amountBlocked = 0;
        bool allBlocked = true;
        for (int i = 0; i < names.size(); i++) {
            if (blockTimes[i] > amountBlocked) {
                amountBlocked = blockTimes[i];
            }
            if (blockTimes[i] == 0) {
                allBlocked = false;
            }
        }
        
        if (allBlocked) {
            currentName = "<idle>";
            status = "I";
            length = amountBlocked;
        }
        else {
            // check if process is terminating or is blocking
            if (total_times[tempCompare] > block_intervals[tempCompare]) { // if the total amount of time is greater than the time for the block interval, it will be blocked before it terminates
                if (length >= block_intervals[tempCompare]) {
                    status = "B";
                    length = block_intervals[tempCompare];
                    blockTimes[tempCompare] = block_duration+length;
                }
                else {
                    status = "S";
                }
            }
            else {
                if (length >= total_times[tempCompare]) {
                    status = "T";
                    length = total_times[tempCompare];
                }
                else {
                    status = "S";
                }
            }
            total_times[tempCompare] -= length;
            block_intervals[tempCompare] -= length;
        }
        
        // update tempCompare (look for next non-blocked process)
        if (names.size() == 1)
            tempCompare = 0;
        else if (!allBlocked) {
            while (true) {
                if (tempCompare == names.size()-1)
                    tempCompare = 0;
                else
                    tempCompare++;
                if (blockTimes[tempCompare] == 0)
                    break;
            }
        }
        else {
            int temp = 0;
            for (int i = 0; i < names.size(); i++) {
                if (blockTimes[i] > blockTimes[temp])
                    tempCompare = i;
            }        
        }
        
        // update blockTimes
        for (int i = 0; i < blockTimes.size(); i++){
            if (blockTimes[i] > length) {
                blockTimes[i] -= length;
            }
            else if (blockTimes[i] <= length && blockTimes[i] > 0) {
                blockTimes[i] = 0;
                block_intervals[i] = block_intervals[i+block_intervals.size()/2];
            }
        }

        // print out            
        if (names.size() == 0) {
            cout << " " << currentTime << "\t" << "<done>" << "\t" << turnaroundTime/initialSize << "\t" << endl;
            loop = false;
        } else {
            cout << " " << currentTime << "\t" << currentName << "\t" << length << "\t" << status << "\t" << endl;
//            cout << "block times: " << blockTimes[0] << " " << blockTimes[1] << " " << blockTimes[2] << endl;
        }
        currentTime += length;
    }
}

//void RoundRobin::Execute() {
//    // Organize arrays into order of arrival time
//    // Iterator through each process until they are done, switching every 10
//}

