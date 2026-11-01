//
// Created by thedi on 10/29/2026.
//

#include "infonode.h"
InfoNode::InfoNode(int sleepQuality_,int sleepDuration_,int sleepLatency_, double stressScore_, double workHours_, double caffeineMg_, double screenTime_) {
    sleepQuality = sleepQuality_;
    sleepDuration = sleepDuration_;
    sleepLatency = sleepLatency_;
    stressScore = stressScore_;
    workHours = workHours_;
    caffeineMg = caffeineMg_;
    screenTime = screenTime_;
}