//
// Created by Copper on 10/25/2026.
//

#ifndef ESTIMATEDSLEEPTIME_COMPILE_H
#define ESTIMATEDSLEEPTIME_COMPILE_H
#include <map>
#include <vector>
#include <utility>
#include <string>

class compiler {
    std::map<int, std::vector<std::pair<double, double>>> sleepMap;

public:
    compiler();
    void compile();
    void iterate(int key) const;
};
#endif //ESTIMATEDSLEEPTIME_COMPILE_H