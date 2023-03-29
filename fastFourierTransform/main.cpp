#include "src/src.h"
#include "src/config.h"


int main(int argc, char* argv[]){
    #ifdef _OPENMP
    omp_set_dynamic(0);
    omp_set_num_threads(10);
    #endif
    #ifdef _OPENMP
    omp_set_dynamic(0);
    omp_set_num_threads(10);
    #endif
    config *cfg = NULL;
    ParseArguments(argc, argv, cfg);
    
    for (auto size : cfg->size){
        std::chrono::milliseconds minDuration = std::chrono::
                                                     milliseconds::max();
        std::complex<double> *inputSignal = NULL;
        std::complex<double> *outputSignal = NULL;

        ProcessInitalization(inputSignal, outputSignal, size, cfg);
        for (int i = 0; i < cfg->repeatCount; i++){
            auto begin = std::chrono::steady_clock::now();
            FastFourierTransform(inputSignal, outputSignal, size, cfg);
            auto end = std::chrono::steady_clock::now();
            auto duration = std::chrono::
                            duration_cast<std::chrono::
                                          milliseconds>(end - begin);
            if (minDuration.count() > duration.count())
                minDuration = duration;
        }
        printf("Execution time is: %f\n", minDuration.count() * 1e-3);
        if (cfg->is_print)
            PrintSignal(outputSignal, size);
        ProcessTermination(inputSignal, outputSignal);
    }   
}