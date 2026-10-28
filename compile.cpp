#include "compile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ranges>
#include <cmath>

//This'll be used to compile both the hashmap and the heap or we can actually do a separate program for each
double mapCompiler::calculateLatencyScore(int latencyDuration) {
    const double L = std::max(0.0, static_cast<double>(latencyDuration));
    const double ideal = 12.0;
    // Lopsided: falling asleep slowly is penalized more than falling asleep fast
    const double sigma = (L < ideal) ? 8.0 : 15.0;
    const double d = L - ideal;
    return std::exp(-(d * d) / (2.0 * sigma * sigma));
}
double mapCompiler::calculateSleepDurationScore(int sleepDuration) {
    const double D = std::max(0.0, static_cast<double>(sleepDuration));
    const double ideal = 480.0;  // 8 h
    const double sigma = 90.0;   // 1.5 h
    const double d = D - ideal;
    return std::exp(-(d * d) / (2.0 * sigma * sigma));
}
double mapCompiler::calculateSleepQuality(int sleepDuration, int latencyDuration) {
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
void mapCompiler::compile() {
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

        double timeToSleep = std::stoi(row[10]);
        double caffeineMg = std::stod(row[12]);
        double screenMins = std::stod(row[14]);
        int sleepMinutes = static_cast<int>(std::lround(sleepHrs*60));
        double sleepQuality = calculateSleepQuality(sleepMinutes,timeToSleep);
        int durationKey = static_cast<int>(std::lround(sleepHrs*60));
        //std::cout << key<<std::endl;
        sleepDurationMap[durationKey].push_back({stressScore, workHours});
        timeToSleepMap[timeToSleep].push_back({caffeineMg,screenMins});
        sleepQualityMap[sleepQuality].push_back({sleepMinutes,timeToSleep, stressScore,workHours, caffeineMg, screenMins});
    }
}

void mapCompiler::iterate(int key) const {
    auto it = sleepDurationMap.find(key);
    if (it == sleepDurationMap.end()) {
        std::cout << "No entries for key " << key << "\n";
        return;
    }
    for (const auto& [caffeine, screen] : it->second) {
        std::cout << caffeine << " mg, " << screen << " mins\n";
    }
}
std::pair<double,double> mapCompiler::averageDurationRange(int start, int end) {
    std::pair<double,double> final = {-1,-1};
    int count = 0;
    double stressScore = 0;
    double workHours = 0;
    //loop through all pairs
    for (int i = start; i<end;i++) {
        auto it = sleepDurationMap.find(i);
        if (it != sleepDurationMap.end()) {
            //Loop through any elements in the vector
            //std::cout <<it->second.size()<<std::endl;
            for (int j = 0;j<it->second.size();j++) {
                count++;
                stressScore += it->second[j].first;
                workHours += it->second[j].second;
            }
        }
    }
    if (count != 0) {
        stressScore /= count;
        workHours /= count;
    }
    final = {stressScore,workHours};

    return final;
}
std::pair<double,double> mapCompiler::averageLatencyRange(int start, int end) {
    std::pair<double,double> final = {-1,-1};
    int count = 0;
    double caffeineMg = 0;
    double screenTime = 0;
    //loop through all pairs
    for (int i = start; i<end;i++) {
        auto it = timeToSleepMap.find(i);
        if (it != timeToSleepMap.end()) {
            //Loop through any elements in the vector
            //std::cout <<it->second.size()<<std::endl;
            for (int j = 0;j<it->second.size();j++) {
                count++;
                caffeineMg += it->second[j].first;
                screenTime += it->second[j].second;
            }
        }
    }
    if (count != 0) {
        caffeineMg /= count;
        screenTime /= count;
    }
    final = {caffeineMg,screenTime};

    return final;
}
//this is the best/worst X sleepers by duration. Reverse is best.
std::tuple<int,double,double> mapCompiler::averageDurationCount(int count, bool reverse) {
    int averageMinutes = 0;
    double averageStress = 0;
    double averageWork=0;
    int amount = 0;
    std::tuple<int,double,double> final = {-1,-1,-1};
    if (reverse) {
        for (const auto& [sleepMinutes, sleepVector] : sleepDurationMap | std::views::reverse) {
            for (int i = 0; i<sleepVector.size();i++) {
                if (amount >= count) {
                    break;
                }
                averageMinutes+= sleepMinutes;
                averageStress += sleepVector[i].first;
                averageWork += sleepVector[i].second;
                amount++;
            }
            if (amount >= count) {
                break;
            }
        }
    }
    else {
        for (const auto& [sleepMinutes, sleepVector] : sleepDurationMap) {
            for (int i = 0; i<sleepVector.size();i++) {
                if (amount >= count) {
                    break;
                }
                averageMinutes+= sleepMinutes;
                averageStress += sleepVector[i].first;
                averageWork += sleepVector[i].second;
                amount++;
            }
            if (amount >= count) {
                break;
            }
        }
    }

    if (amount !=0) {
        averageMinutes /= amount;
        averageStress /= amount;
        averageWork /=amount;
        final = {averageMinutes,averageStress, averageWork};
    }
    return final;
}
std::tuple<int,double,double> mapCompiler::averageLatencyCount(int count, bool reverse) {
    int averageMinutes = 0;
    double averageStress = 0;
    double averageWork=0;
    int amount = 0;
    std::tuple<int,double,double> final = {-1,-1,-1};
    if (reverse) {
        for (const auto& [sleepMinutes, sleepVector] : sleepDurationMap | std::views::reverse) {
            for (int i = 0; i<sleepVector.size();i++) {
                if (amount >= count) {
                    break;
                }
                averageMinutes+= sleepMinutes;
                averageStress += sleepVector[i].first;
                averageWork += sleepVector[i].second;
                amount++;
            }
            if (amount >= count) {
                break;
            }
        }
    }
    else {
        for (const auto& [sleepMinutes, sleepVector] : sleepDurationMap) {
            for (int i = 0; i<sleepVector.size();i++) {
                if (amount >= count) {
                    break;
                }
                averageMinutes+= sleepMinutes;
                averageStress += sleepVector[i].first;
                averageWork += sleepVector[i].second;
                amount++;
            }
            if (amount >= count) {
                break;
            }
        }
    }

    if (amount !=0) {
        averageMinutes /= amount;
        averageStress /= amount;
        averageWork /=amount;
        final = {averageMinutes,averageStress, averageWork};
    }
    return final;

}

mapCompiler::mapCompiler() {

}