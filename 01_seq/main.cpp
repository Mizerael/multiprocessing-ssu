#ifdef _OPENMP
#include <omp.h>
#endif

#include "source/exp.h"

int main(){
    int i;
    double time, res, min_time, max_time, avg_time;
    int numbExp, h;
    std::cout << "get count experiment: ";
    std::cin >> numbExp;
    std::cout << "\n get count seuqurnces: ";
    std::cin >> h;
    min_time = max_time = avg_time = experiment(&res, h);
    for (i = 0; i < numbExp; i++){
        time = experiment(&res, h);
        avg_time += time;
        if (max_time < time) max_time = time;
        if (min_time > time) min_time = time;
        std::cout << "execution time : " << avg_time / numbExp << "; " <<
                     min_time << "; " << max_time << "\n";
        std::cout.precision(8);
        std::cout << "integral value: " << res << "\n"; 
    }
    return 0;
}