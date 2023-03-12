#include "src.h"

void DummyDataInitialization(std::complex<double> *mas, int size){
    for (int i = 0; i < size; ++i)
        mas[i] = 0;
    mas[size - size / 4] = 1;
}
//Memory allocation
void ProcessInitalization(std::complex<double> *&inputSignal,
                          std::complex<double> *&outputSignal, int &size,
                          config *cfg){
    do {
        std::cout << "Set length of input signal:";
        std::cin >> size;
        if (size < 4)
            std::cout << "Input signal length should be >= 4\n";
        else {
            int tmpSize = size;
            while (tmpSize != 1) {
                if (tmpSize % 2 != 0){
                    std::cout << "Input signal length should be powers of 2\n";
                    size--;
                    break; 
                }
                tmpSize /= 2;
            }
        }
    } while (size < 4);
    std::cout << "Input signal length: " << size << '\n';
    inputSignal = new std::complex<double>[size];
    outputSignal = new std::complex<double>[size];
    //Test initialization of input elements
    if (cfg->dataInitialization)
        RandomDataInitialization(inputSignal, size);
    else
        DummyDataInitialization(inputSignal, size);
}
//Process termination
void ProcessTermination(std::complex<double> *&inputSignal,
                        std::complex<double> *&outputSignal){
    delete[] inputSignal;
    inputSignal = NULL;
    delete[] outputSignal;
    outputSignal = NULL;
}

void BitReversing(std::complex<double> *inputSignal,
                  std::complex<double> *outputSignal, int size){
    int i = 0, j = 0;
    while (i < size) {
        if (j > i) {
            outputSignal[i] = inputSignal[j];
            outputSignal[j] = inputSignal[i];
        } else if (i == j)
            outputSignal[i] = inputSignal[i];
        int m = size >> 1;
        while ((m >= 1) && (j >= m)) {
            j -= m;
             m = m >> 1;
        }
        j += m;
        i++;
    }
}

inline void Butterfly(std::complex<double> *signal, std::complex<double> u,
                      int offset, int butterflySize){
    std::complex<double> tem = signal[offset + butterflySize] * u;
    signal[offset + butterflySize] = signal[offset] - tem;
    signal[offset] += tem;
}

void SerrialFFTCalculation(std::complex<double> *signal, int size){
    int m = 0;
    for (int tmp_size = size; tmp_size > 1; tmp_size /= 2, m++);
    for (int p = 0; p < m; p++) {
        int butterflyOffset = 1 << (1 + p);
        int butterflySize = butterflyOffset >> 1;
        double coeff = M_PI / butterflySize;
        for (int i = 0; i < size / butterflyOffset; i++)
            for (int j = 0; j < butterflySize; j++)
                Butterfly(signal, 
                          std::complex<double>(cos(-j * coeff),sin(-j * coeff)),
                          j + i * butterflyOffset, butterflySize);
    }
}

void SerrialFFT(std::complex<double> *inputSignal,
                std::complex<double> *outputSignal, int size){
    BitReversing(inputSignal, outputSignal, size);
    SerrialFFTCalculation(outputSignal, size);
}

void PrintSignal(std::complex<double> *signal, int size){
    std::cout << "Result signal:\n";
    for(int i = 0; i < size; i++)
        std::cout << signal[i] << '\n';
}

void RandomDataInitialization(std::complex<double> *mas, int size){
    srand(unsigned(clock()));
    for(int i = 0; i < size; i++)
        mas[i] = std::complex<double>(rand() / 1000.0, rand() / 1000.0);
}