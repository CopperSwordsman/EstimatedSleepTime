#include <iostream>
#include "compile.h"
int main() {
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
    c.iterate(5);
    return 0;
}