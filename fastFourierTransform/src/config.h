#ifndef cfgFFT_H
#define cfgFFT_H
#include <vector>

struct config{
    std::vector<int> size;
    bool dataInitialization = false;
};

void ParseArguments(int argc, char * argv[], config *&cfg);
#endif