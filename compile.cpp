#include "compile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

void compiler::compile() {
    std::ifstream file("sleep_health_dataset.csv");
    if (!file) {
        std::cerr << "Could not open sleep_data.csv\n";
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
        double caffeineMg = std::stod(row[12]);
        double screenMins = std::stod(row[14]);

        int key = static_cast<int>(std::lround(sleepHrs*60));
        //std::cout << key<<std::endl;
        sleepMap[key].push_back({caffeineMg, screenMins});
    }
}

void compiler::iterate(int key) const {
    auto it = sleepMap.find(key);
    if (it == sleepMap.end()) {
        std::cout << "No entries for key " << key << "\n";
        return;
    }
    for (const auto& [caffeine, screen] : it->second) {
        std::cout << caffeine << " mg, " << screen << " mins\n";
    }
}
compiler::compiler() {

}