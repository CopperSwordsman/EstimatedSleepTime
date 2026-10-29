#include "compile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ranges>
#include <cmath>
#include "maps.h"
#include "infonode.h"
double compiler::calculateLatencyScore(int latencyDuration) {
    const double L = std::max(0.0, static_cast<double>(latencyDuration));
    const double ideal = 12.0;
    // Lopsided: falling asleep slowly is penalized more than falling asleep fast
    const double sigma = (L < ideal) ? 8.0 : 15.0;
    const double d = L - ideal;
    return std::exp(-(d * d) / (2.0 * sigma * sigma));
}
double compiler::calculateSleepDurationScore(int sleepDuration) {
    const double D = std::max(0.0, static_cast<double>(sleepDuration));
    const double ideal = 480.0;  // 8 h
    const double sigma = 90.0;   // 1.5 h
    const double d = D - ideal;
    return std::exp(-(d * d) / (2.0 * sigma * sigma));
}
double compiler::calculateSleepQuality(int sleepDuration, int latencyDuration) {
    //calculate latencyScore
    double latencyScore;
    double durationScore;
    const double latencyWeight = 0.35;
    const double durationWeight = 0.65;
    const double floorVal = 0.05;
    latencyScore = std::max(floorVal,calculateLatencyScore(latencyDuration));
    durationScore = std::max(floorVal,calculateSleepDurationScore(sleepDuration));

    //calculate durationScore
    return 100.0 * std::pow(durationScore, durationWeight) * std::pow(latencyScore, latencyWeight);
}
void compiler::compile(CustomMap& sleepMap) {
    std::ifstream file("sleep_health_dataset.csv");
    if (!file) {
        std::cerr << "Could not open sleep_health_dataset.csv\n";
        return;
    }
    std::string line;
    std::getline(file, line);   // skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        if (row.size() < 15) {
            continue;
        }
        double sleepHrs   = std::stod(row[6]);
        double stressScore = std::stod(row[18]);
        double workHours = std::stod(row[19]);

        double sleepLatency = std::stoi(row[10]);
        double caffeineMg = std::stod(row[12]);
        double screenTime = std::stod(row[14]);
        int sleepDuration = static_cast<int>(std::lround(sleepHrs*60));
        int sleepQuality = static_cast<int>(calculateSleepQuality(sleepDuration,sleepLatency));
        int durationKey = static_cast<int>(std::lround(sleepHrs*60));
        InfoNode info_node(sleepQuality,sleepDuration,sleepLatency,stressScore,workHours,caffeineMg,screenTime);
        sleepMap[sleepQuality].addNode(info_node);
    }
}
compiler::compiler() {
}