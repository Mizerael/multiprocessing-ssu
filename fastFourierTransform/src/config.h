#ifndef cfgFFT_H
#define cfgFFT_H
#include <vector>

struct config{
    std::vector<int> size;
    bool dataInitialization = false;
    int repeatCount = 16;
    bool is_print = false;
    bool parralel_bit = false;
};

void ParseArguments(int argc, char * argv[], config *&cfg);
#endif