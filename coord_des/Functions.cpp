#include <vector>
#include "Functions.h"

double f1::operator()(const std::vector<double>& x) const  {
    double res = (1 - x[0]) * (1 - x[0]) + 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]);
    return res;
}

double f2::operator()(const std::vector<double>& x) const {
    double res = 5 * x[0] * x[0] + 6 * x[0] * x[1] + 5 * x[1] * x[1];
    return res;
}

double f3::operator()(const std::vector<double>& x) const {
    double res = 0;
    for (int i = 0; i < x.size(); ++i) {
        res += x[i] * x[i] + 2 * x[i];
    }
    return res; 
}