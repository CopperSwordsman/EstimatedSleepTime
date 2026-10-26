#include <iostream>
#include "compile.h"
#include "Load_window.h"

int main() {
    mapCompiler c;
    c.compile();
    //c.iterate(481);
    std::pair<double,double> testDurationPair;
    testDurationPair = c.averageDurationRange(500,600);
    std::cout <<"Average Stress Level: " << testDurationPair.first << "\n" << "Average Work Hours: " << testDurationPair.second << std::endl;

    //latency goes up to about 58 apparently
    std::pair<double,double> testLatencyPair;
    testLatencyPair = c.averageLatencyRange(0,10);
    std::cout<<"\nAverage Caffeine MG: " << testLatencyPair.first << "\n" << "Average Screentime Before Bed: " << testLatencyPair.second << std::endl;

    //SFML Window
    Game game;
    game.run();


    return 0;
}