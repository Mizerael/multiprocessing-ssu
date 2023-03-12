#ifndef FFTSRC_H
#define FFTSRC_H
#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <chrono>
#include <vector>
#ifdef _OPENMP
#include <omp.h>
#endif
#include "config.h"

void DummyDataInitialization(std::complex<double> *mas, int size);

void RandomDataInitialization(std::complex<double> *mas, int size);

void ProcessInitalization(std::complex<double> *&inputSignal,
                          std::complex<double> *&outputSignal, int &size,
                          config *cfg);

void ProcessTermination(std::complex<double> *&inputSignal,
                        std::complex<double> *&outputSignal);

void BitReversing(std::complex<double> *inputSignal,
                  std::complex<double> *outputSignal, int size);

void ParralelBitReversing(std::complex<double> *inputSignal,
                  std::complex<double> *outputSignal, int size);

inline void Butterfly(std::complex<double> *signal, std::complex<double> u,
                      int offset, int butterflySize);

void FFTCalculation(std::complex<double> *signal, int size);

void FastFourierTransform(std::complex<double> *inputSignal,
                std::complex<double> *outputSignal, int size, config *cfg);

void PrintSignal(std::complex<double> *signal, int size);
#endif