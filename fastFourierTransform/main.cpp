#include "src/src.h"
#include "src/config.h"
int main(int argc, char* argv[]){
    config *cfg = NULL;
    ParseArguments(argc, argv, cfg);
    std::complex<double> *inputSignal = NULL;
    std::complex<double> *outputSignal = NULL;
    int size = 0;
    std::cout <<"Fast Fourier Transform\n";
    ProcessInitalization(inputSignal, outputSignal, size, cfg);
    SerrialFFT(inputSignal, outputSignal, size);
    PrintSignal(outputSignal, size);
    ProcessTermination(inputSignal, outputSignal);
}