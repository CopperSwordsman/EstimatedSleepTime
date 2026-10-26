#include "compile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

//This'll be used to compile both the hashmap and the heap or we can actually do a separate program for each
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

        int durationKey = static_cast<int>(std::lround(sleepHrs*60));
        //std::cout << key<<std::endl;
        sleepDurationMap[durationKey].push_back({stressScore, workHours});
        timeToSleepMap[timeToSleep].push_back({caffeineMg,screenMins});
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

mapCompiler::mapCompiler() {

}