/* 
 * File:   main.cpp
 * Author: Grant Kochmann and Maxwell Evans
 *
 * Created on February 8, 2018, 4:24 PM
 */

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Scheduler.h"
using namespace std;

int main(int argc, char** argv) {
    
    // Check if all arguments are inputted
    if (argc != 4) {
        cerr << "Either file name, block duration, or time slice not specified." << endl;
        exit(1);
    }
    
    // Create fstream to open file
    fstream inFile;
    string fileName = argv[1];
    inFile.open(fileName);
    if (inFile.fail()) { // Exit program if it can't open file
        cerr << "ERROR: Unable to open text file: " << fileName << endl;
        exit(1);
    }
    int block_duration = atoi(argv[2]);
    int time_slice = atoi(argv[3]);
    
    // Read text file
    vector<string> names;
    vector<int> arrival_times;
    vector<int> total_times;
    vector<int> block_intervals;
    
    string tempLine, tempWord;
    int tempNum1, tempNum2, tempNum3;
    while (getline(inFile, tempLine)) {
        std::istringstream iss(tempLine);
        while (iss >> tempWord >> tempNum1 >> tempNum2 >> tempNum3) {
            names.push_back(tempWord);
            arrival_times.push_back(tempNum1);
            total_times.push_back(tempNum2);
            block_intervals.push_back(tempNum3);
        }
    }
    
//    ofstream cout("output.txt");
//    std::cout.rdbuf(cout.rdbuf());
    
    // Execute Round Robin
//    cout << "RR " << block_duration << " " << time_slice << endl;
    Scheduler scheduler(names, arrival_times, total_times, block_intervals);
//    scheduler.RoundRobin(block_duration, time_slice);
    
    // Execute Shortest Process Next
    cout << "SPN " << block_duration << endl;
    //Scheduler scheduler2(names, arrival_times, total_times, block_intervals);
    scheduler.ShortestProcessNext(block_duration);
    
    return 0;
}

