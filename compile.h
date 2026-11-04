//
// Created by Copper on 10/25/2026.
//

#ifndef ESTIMATEDSLEEPTIME_COMPILE_H
#define ESTIMATEDSLEEPTIME_COMPILE_H
#include <map>
#include <vector>
#include <utility>
#include "maps.h"
#include "Heap.h"

class compiler {
public:
    compiler();
    void compile(CustomMap& sleepMap, Heap& minSleepHeap, Heap& maxSleepHeap);
    double calculateSleepQuality(int sleepDuration, int latencyDuration);
    double calculateLatencyScore(int latencyDuration);
    double calculateSleepDurationScore(int sleepDuration);
};
#endif //ESTIMATEDSLEEPTIME_COMPILE_H