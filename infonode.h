//
// Created by thedi on 10/29/2026.
//

#ifndef ESTIMATEDSLEEPTIME_INFONODE_H
#define ESTIMATEDSLEEPTIME_INFONODE_H
enum class InfoNodeType{
    sleepQuality,
    sleepDuration,
    sleepLatency,
    stressScore,
    workHours,
    caffeineMg,
    screenTime
};
struct InfoNode {
    int sleepQuality;
    int sleepDuration;
    int sleepLatency;
    double stressScore;
    double workHours;
    double caffeineMg;
    double screenTime;
    InfoNode(int sleepQuality_,int sleepDuration_,int sleepLatency_, double stressScore_, double workHours_, double caffeineMg_, double screenTime_);
};
#endif //ESTIMATEDSLEEPTIME_INFONODE_H