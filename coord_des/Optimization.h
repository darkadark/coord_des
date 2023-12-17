#pragma once
#include <random>
#include "StopCriterion.h"
#include <functional>
#include "Functions.h"


class OnedimOpt {

public:
    virtual ~OnedimOpt() {}
    virtual double Optimize(double r, double l, std::function<double(double)> f) = 0;
};

class MultdimOpt {
protected:
    const func& f;
    std::vector<double> r;
    std::vector<double> l;
    StopCriterion& stop_crit;
public:
    MultdimOpt(const func& f_,
        const std::vector<double>& r_,
        const std::vector<double>& l_,
        StopCriterion& stop_crit_) :
        f(f_), r(r_), l(l_), stop_crit(stop_crit_)
    {}
    virtual std::vector<double> Optimize(const std::vector<double>& x) = 0;
};

class DetermineSearch : public MultdimOpt {
    OnedimOpt* onedim_opt;
public:
    DetermineSearch(const func& f_,
        const std::vector<double>& r_,
        const std::vector<double>& l_,
        StopCriterion& stop_crit_,
        OnedimOpt* onedim_opt_) :
        MultdimOpt(f_, r_, l_, stop_crit_), onedim_opt(onedim_opt_)
    {}
    ~DetermineSearch() { delete onedim_opt; }
    std::vector<double> Optimize(const std::vector<double>& x) override;
};

class TernarySearch : public OnedimOpt {
    double eps;
public:
    TernarySearch(double eps_) : eps(eps_) {}
    double Optimize(double r, double l, std::function<double(double)> f) override;
};


class RandomSearch : public MultdimOpt {
    std::vector<double> GenY();
    std::vector<std::uniform_real_distribution<double>> dist;
public:
    RandomSearch(const func& f_,
        const std::vector<double>& r_,
        const std::vector<double>& l_,
        StopCriterion& stop_crit_) :
        MultdimOpt(f_, r_, l_, stop_crit_)
    {
        dist.reserve(r.size());
        for (int i = 0; i < r.size(); ++i) {
            dist.emplace_back(l[i], r[i]);
        }

    }
    std::vector<double> Optimize(const std::vector<double>& x) override;
};

