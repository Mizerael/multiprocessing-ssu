#include "src/src.h"

int main(){
    std::complex<double> *inputSignal = NULL;
    std::complex<double> *outputSignal = NULL;
    int size = 0;
    std::cout <<"Fast Fourier Transform\n";
    ProcessInitalization(inputSignal, outputSignal, size);
    SerrialFFT(inputSignal, outputSignal, size);
    PrintSignal(outputSignal, size);
    ProcessTermination(inputSignal, outputSignal);
}