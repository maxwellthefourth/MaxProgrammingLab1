///* 
// * File:   RoundRobin.cpp
// * Author: Grant Kochmann and Maxwell Evans
// * 
// * Created on February 10, 2018, 2:04 PM
// */
//
//#include "Scheduler.h"
//
//void Scheduler::RoundRobin() {
//    for(int i = 0; i < names.size(); i++){ //Adding all of the processes to queue
//        Process p;
//        p.name = names[i];
//        p.arrival_time = arrival_times[i];
//        p.block_interval = block_intervals[i];
//        p.total_time = total_times[i];
//    }
//    
//    simulationTime = 0;
//    
//    int block_duration;
//    int time_slice;
//    
//    int tempCompare = 0;
//    int temp = block_intervals.size();
//    block_intervals.resize(block_intervals.size()*2);
//    for (int i = 0; i < temp; i++) {
//        block_intervals[temp+i] = block_intervals[i];
//    }
//    
//    int currentTime = simulationTime; // Initialize current time
//    string currentName = names[0]; // Set first to default name
//    int length = time_slice; // Initialize length
//    string status = "temp"; // Initialize status
//    vector<int> blockTimes(names.size(), 0); // Create a vector to see which are blocked
//    double turnaroundTime = 0;
//    int initialSize = names.size();
//    
//    bool loop = true;
//    while (loop) {
//        currentName = names[tempCompare];
//        length = time_slice;
//        
//        // Remove process from queue once it finishes
//        if (total_times[tempCompare] == 0) {
//            turnaroundTime += currentTime;
//            names.erase(names.begin()+tempCompare);
//            arrival_times.erase(arrival_times.begin()+tempCompare);
//            total_times.erase(total_times.begin()+tempCompare);
//            block_intervals.erase(block_intervals.begin()+tempCompare);
//            blockTimes.erase(blockTimes.begin()+tempCompare);
//        }
//
//        // check if blocked
//        int amountBlocked = 0;
//        bool allBlocked = true;
//        for (int i = 0; i < names.size(); i++) {
//            if (blockTimes[i] > amountBlocked) {
//                amountBlocked = blockTimes[i];
//            }
//            if (blockTimes[i] == 0) {
//                allBlocked = false;
//            }
//        }
//        
//        if (allBlocked) {
//            currentName = "<idle>";
//            status = "I";
//            length = amountBlocked;
//        }
//        else {
//            // check if process is terminating or is blocking
//            if (total_times[tempCompare] > block_intervals[tempCompare]) { // if the total amount of time is greater than the time for the block interval, it will be blocked before it terminates
//                if (length >= block_intervals[tempCompare]) {
//                    status = "B";
//                    length = block_intervals[tempCompare];
//                    blockTimes[tempCompare] = block_duration+length;
//                }
//                else {
//                    status = "S";
//                }
//            }
//            else {
//                if (length >= total_times[tempCompare]) {
//                    status = "T";
//                    length = total_times[tempCompare];
//                }
//                else {
//                    status = "S";
//                }
//            }
//            total_times[tempCompare] -= length;
//            block_intervals[tempCompare] -= length;
//        }
//        
//        // update tempCompare (look for next non-blocked process)
//        if (names.size() == 1)
//            tempCompare = 0;
//        else if (!allBlocked) {
//            while (true) {
//                if (tempCompare == names.size()-1)
//                    tempCompare = 0;
//                else
//                    tempCompare++;
//                if (blockTimes[tempCompare] == 0)
//                    break;
//            }
//        }
//        else {
//            int temp = 0;
//            for (int i = 0; i < names.size(); i++) {
//                if (blockTimes[i] > blockTimes[temp])
//                    tempCompare = i;
//            }        
//        }
//        
//        // update blockTimes
//        for (int i = 0; i < blockTimes.size(); i++){
//            if (blockTimes[i] > length) {
//                blockTimes[i] -= length;
//            }
//            else if (blockTimes[i] <= length && blockTimes[i] > 0) {
//                blockTimes[i] = 0;
//                block_intervals[i] = block_intervals[i+block_intervals.size()/2];
//            }
//        }
//
//        // print out            
//        if (names.size() == 0) {
//            cout << " " << currentTime << "\t" << "<done>" << "\t" << turnaroundTime/initialSize << "\t" << endl;
//            loop = false;
//        } else {
//            cout << " " << currentTime << "\t" << currentName << "\t" << length << "\t" << status << "\t" << endl;
////            cout << "block times: " << blockTimes[0] << " " << blockTimes[1] << " " << blockTimes[2] << endl;
//        }
//        currentTime += length;
//    }
//}
//
////void RoundRobin::Execute() {
////    // Organize arrays into order of arrival time
////    // Iterator through each process until they are done, switching every 10
////}
//
//
