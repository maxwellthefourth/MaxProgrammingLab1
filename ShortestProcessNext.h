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
private:

};

#endif /* SHORTESTPROCESSNEXT_H */

