//
// Created by Copper on 10/25/2026.
//

#ifndef ESTIMATEDSLEEPTIME_COMPILE_H
#define ESTIMATEDSLEEPTIME_COMPILE_H
#include <map>
#include <vector>
#include <utility>
#include <string>

class mapCompiler {

    std::map<int, std::vector<std::pair<double, double>>> timeToSleepMap;
    //first is going to be stressScore, second will be workHours.
    std::map<int, std::vector<std::pair<double,double>>> sleepDurationMap;
public:
    mapCompiler();
    void compile();
    void iterate(int key) const;
    std::pair<double,double> averageDurationRange(int start, int end);
    std::pair<double,double> averageLatencyRange(int start, int end);
};
class heapCompiler {
public:
    heapCompiler();
    void compile();
};
#endif //ESTIMATEDSLEEPTIME_COMPILE_H