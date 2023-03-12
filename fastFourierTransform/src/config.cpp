#include <stdlib.h>
#include "config.h"
#include <iostream>

void ParseArguments(int argc, char* argv[], config *&cfg){
    cfg = new config;
    for(int i = 1; i < argc; i++){
        if ((std::string)argv[i] == "-t")
            cfg->dataInitialization = true;
        else if ((std::string)argv[i] == "-s") {
            int j = i + 1;
            for (j ; j < argc; j++){
                auto val = atoi(argv[j]);
                if (val)
                    cfg->size.push_back(val);
                else break;
                }
            i = j - 1;
        }
    }
}