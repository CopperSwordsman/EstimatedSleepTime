#include <iostream>
#include "compile.h"
#include "maps.h"
#include "Load_window.h"

int main() {


    /*
    mapCompiler c;
    c.compile();
    //c.iterate(481);
    std::pair<double,double> testDurationPair;
    testDurationPair = c.averageDurationRange(0,250);
    std::cout <<"Average Stress Level: " << testDurationPair.first << "\n" << "Average Work Hours: " << testDurationPair.second << std::endl;

    //latency goes up to about 58
    std::pair<double,double> testLatencyPair;
    testLatencyPair = c.averageLatencyRange(50,58);
    std::cout<<"\nAverage Caffeine MG: " << testLatencyPair.first << "\n" << "Average Screentime Before Bed: " << testLatencyPair.second << std::endl;

    //best 10 sleepers
    std::tuple<int, double,double> testSleepDurationTuple;
    testSleepDurationTuple = c.averageDurationCount(1000,true);
    std::cout << "\nAverage Sleep minutes: " << std::get<0>(testSleepDurationTuple) << "\nAverage Stress Score " << std::get<1>(testSleepDurationTuple) << "\nAverage Work Hours: " << std::get<2>(testSleepDurationTuple) << std::endl;
    std::cout<<"\n\n";
    c.iterate(5);*/
    //easier to type but technically bad practice
    enum InfoNodeType{
        sleepQuality,
        sleepDuration,
        sleepLatency,
        stressScore,
        workHours,
        caffeineMg,
        screenTime
    };
    // CustomMap m;
    // compiler c;
    // c.compile(m);
    /*for (int i = 5;i<=100;i++) {
        std::cout << i << " Sleep Quality\n";
        std::cout << "Sleep Duration: " << m[i].averageValue(sleepDuration) << std::endl;
        std::cout << "Sleep Latency: " << m[i].averageValue(sleepLatency) << std::endl;
        std::cout << "Stress Score: " << m[i].averageValue(stressScore) << std::endl;
        std::cout << "Work Hours: " << m[i].averageValue(workHours) << std::endl;
        std::cout << "Caffeine MG: " << m[i].averageValue(caffeineMg) << std::endl;
        std::cout << "Screen Time: " << m[i].averageValue(screenTime) << "\n"<< std::endl;
    }*/
    // std::cout << m.averageValues(sleepDuration,95,100) << std::endl;
    // std::cout << m.averageValues(sleepLatency,95,100) << std::endl;
    // std::cout << m.averageValues(stressScore,95,100) << std::endl;
    // std::cout << m.averageValues(workHours,95,100) << std::endl;
    // std::cout << m.averageValues(screenTime,95,100) << std::endl;
    // std::cout << m.averageValues(caffeineMg,95,100) << std::endl;
    // return 0;
    Game EST;
    EST.run();
}