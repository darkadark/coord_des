#pragma once
#include <vector>

class func {
public:
    virtual double operator()(const std::vector<double>& x) const = 0;
    virtual int get_dim() const = 0;
    virtual ~func() {}
};


class f1 : public func {
public:
    double operator()(const std::vector<double>& x) const override;
    int get_dim() const override { return 2; }
};


class f2 : public func {
public:
    double operator()(const std::vector<double>& x) const override;
    int get_dim() const override { return 2; }
};


class f3 : public func {
    int dim;
public:
    f3(int _dim = 3) : dim(_dim) {}
    double operator()(const std::vector<double>& x) const override;
    int get_dim() const override { return dim; }
};
