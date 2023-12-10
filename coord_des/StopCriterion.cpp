#include <vector>
#include "StopCriterion.h"


bool StopCriterionByYEps::NeedStop(const std::vector<double>& x, double y, int n) {
    if (n > 0 && abs(y - y_prev) < eps)
        return true;
    y_prev = y;
    return false;
}



bool StopCriterionByXEps::NeedStop(const std::vector<double>& x, double y, int n) {
    if (n > 0) {
        double measure = 0;
        for (int i = 0; i < x.size(); ++i) {
            measure += (x[i] - x_prev[i]) * (x[i] - x_prev[i]);
        }
        if (measure < eps2)
            return true;
    }
    x_prev = x;
    return false;
}


bool StopCriterionByN::NeedStop(const std::vector<double>& x, double y, int n) {
    if (n >= n_max)
        return true;

    return false;
}