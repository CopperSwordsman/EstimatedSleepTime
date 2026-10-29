//
// Created by Copper on 10/25/2026.
//

#ifndef ESTIMATEDSLEEPTIME_COMPILE_H
#define ESTIMATEDSLEEPTIME_COMPILE_H
#include <map>
#include <vector>
#include <utility>
enum class Color {
    Red,
    Black
};
struct InfoNode {
    int sleepDuration;
    int sleepLatency;
    double stressScore;
    double workHours;
    double caffeineMg;
    double screenTime;
};
class RBNode {
    //what does a red and black node need lets think
    //color: a left right, a value and that value will be a vector with tuples?
    //maybe the tuples is too much though and too hard to gather from how about just the individual values in the object
    //so we could do sleep quality as the key and then have values that contribute to sleep quality under that
    int sleepQuality;
    std::vector<InfoNode> nodes;
public:
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    RBNode(int sleepQuality_, int sleepDuration_, int sleepLatency_, double stressScore_, double workHours_, double caffeineMg_, double screenTime_);
};
class RBTree {
    RBNode* root;
    RBNode* NIL;

    void leftRotate(RBNode* x);
    void rightRotate(RBNode* y);
    void insertCorrection(RBNode* k);
public:
    RBTree();
    void insert(int sleepQuality_, int sleepDuration_, int sleepLatency_, double stressScore_, double workHours_, double caffeineMg_, double screenTime_);

};
class map {
};
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