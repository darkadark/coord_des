#pragma once
#include <vector>

class StopCriterion {
public:
    virtual ~StopCriterion() {}
    virtual bool NeedStop(const std::vector<double>& x, double y, int n) = 0;
};

class StopCriterionByYEps : public StopCriterion {
    double eps;
    double y_prev;
public:
    StopCriterionByYEps(double eps_) : eps(eps_), y_prev(0) {}
    bool NeedStop(const std::vector<double>& x, double y, int n) override;
};

class StopCriterionByXEps : public StopCriterion {
    double eps2;
    std::vector<double> x_prev;
public:
    StopCriterionByXEps(double eps_) : eps2(eps_* eps_) {}
    bool NeedStop(const std::vector<double>& x, double y, int n) override;
};

class StopCriterionByN : public StopCriterion {
    double n_max;
public:
    StopCriterionByN(double n_) : n_max(n_) {}
    bool NeedStop(const std::vector<double>& x, double y, int n) override;
};
