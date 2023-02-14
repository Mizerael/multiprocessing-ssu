
#include "source/exp.h"

int main(){
    int i;
    double time, res, min_time, max_time, avg_time;
    int numbExp = 10;
    std::string str;
    std::cout << "integration method: ";
    std::cin >> str;
    min_time = max_time = avg_time = experiment(&res, str);
    for (i = 0; i < numbExp; i++){
        time = experiment(&res, str);
        avg_time += time;
        if (max_time < time) max_time = time;
        if (min_time > time) min_time = time;
        std::cout << "execution time: " << avg_time / numbExp << "\nmin time: "; 
        std::cout << min_time << "\nmax time: " << max_time << "\n";
        std::cout.precision(8);
        std::cout << "integral value: " << res << "\n"; 
    }
    return 0;
}