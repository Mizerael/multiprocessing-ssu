#ifndef FFTSRC_H
#define FFTSRC_H
#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <chrono>

void DummyDataInitialization(std::complex<double> *mas, int size);

void ProcessInitalization(std::complex<double> *&inputSignal,
                          std::complex<double> *&outputSignal, int &size);

void ProcessTermination(std::complex<double> *&inputSignal,
                        std::complex<double> *&outputSignal);

void BitReversing(std::complex<double> *inputSignal,
                  std::complex<double> *outputSignal, int size);

inline void Butterfly(std::complex<double> *signal, std::complex<double> u,
                      int offset, int butterflySize);

void SerrialFFTCalculation(std::complex<double> *signal, int size);

void SerrialFFT(std::complex<double> *inputSignal,
                std::complex<double> *outputSignal, int size);

void PrintSignal(std::complex<double> *signal, int size);
#endif