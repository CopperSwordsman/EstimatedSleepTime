//
// Created by Copper on 10/25/2026.
//

#ifndef ESTIMATEDSLEEPTIME_COMPILE_H
#define ESTIMATEDSLEEPTIME_COMPILE_H
#include <map>
#include <vector>
#include <utility>

class mapCompiler {

    std::map<int, std::vector<std::pair<double, double>>> timeToSleepMap;
    //first is going to be stressScore, second will be workHours.
    std::map<int, std::vector<std::pair<double,double>>> sleepDurationMap;
    //this is our general quality map
    //sleepMinutes,sleepLatency, stressScore, workHours, caffeineMg, screenTime
    //now that sleepQuality is a thing that can be used in turn to grab things
    std::map<int, std::vector<std::tuple<int,int, double, double,double,double>>> sleepQualityMap;
public:
    mapCompiler();
    void compile();
    void iterate(int key) const;



    std::pair<double,double> averageDurationRange(int start, int end);
    std::pair<double,double> averageLatencyRange(int start, int end);

    std::tuple<int, double,double> averageDurationCount(int count, bool reverse);
    std::tuple<int,double,double> averageLatencyCount(int count, bool reverse);
    double calculateSleepQuality(int sleepDuration, int latencyDuration);
    double calculateLatencyScore(int latencyDuration);
    double calculateSleepDurationScore(int sleepDuration);
};
class heapCompiler {
public:
    heapCompiler();
    void compile();
};
#endif //ESTIMATEDSLEEPTIME_COMPILE_H