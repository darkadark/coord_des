#include <vector>



double f1(const std::vector<double>& x) {

    double res = (1 - x[0]) * (1 - x[0]) + 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]);
    return res;
}

double f2(const std::vector<double>& x) {
    double res = 5 * x[0] * x[0] + 6 * x[0] * x[1] + 5 * x[1] * x[1];
    return res;
}

double f3(const std::vector<double>& x) {
    double res = 0;
    for (int i = 0; i < x.size(); ++i) {
        res += x[i] * x[i] + 2*x[i];
    }
    return res;
}
