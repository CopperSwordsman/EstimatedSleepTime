#include <iostream>
#include "compile.h"
int main() {
    compiler c;
    c.compile();
    c.iterate(480);
    return 0;
}