#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include "Optimization.h"
#include "Functions.h"



int main()
{
    double eps = -1;
    
    std::cout << "COORDINATE DESCENT" << std::endl;
    std::cout << "\nFunctions:" << std::endl;
    std::cout << "1) (1 - x)^2 + 100(y - x^2)^2" << std::endl;
    std::cout << "2) 5x^2 + 6xy + 5y^2"<< std::endl;
    std::cout << "3) x^2 + y^2 + z^2 + 2x + 2y + 2z" << std::endl;
    std::cout << "Select function: ";
    std::unique_ptr<func> f = nullptr;
    while (!f)
    {
        int func_num;
        std::cin >> func_num;
        switch (func_num) {
        case 1:
            f = std::make_unique<f1>(); 
            break;
        case 2:
            f = std::make_unique<f2>(); 
            break;
        case 3:
            f = std::make_unique<f3>(); 
            break;
        default:
            std::cout << "Error number" << std::endl;
        }
    }

    const int dim = f->get_dim();
    std::cout << std::endl;
    std::vector<double> x_0(dim);
    std::cout << "Enter starting point" << std::endl;
    double xi;
    for (int i = 0; i < dim; ++i) {
        std::cout << "Coordinate " << i+1 <<": ";
        std::cin >> xi;
        x_0[i] = xi;
    }

    std::cout << std::endl;
    std::vector<double> l(dim);
    std::cout << "Set left border" << std::endl;
    for (int i = 0; i < dim; ++i) {
        std::cout << "Coordinate " << i+1 << ": ";
        std::cin >> xi;
        l[i] = xi;
    }
    std::cout << std::endl;
    std::vector<double> r(dim);
    std::cout << "Set right border" << std::endl;
    for (int i = 0; i < dim; ++i) {
        std::cout << "Coordinate " << i+1 << ": ";
        std::cin >> xi;
        r[i] = xi;
    }

    double p = -1;
    double delta = -1;
    std::cout << "\nOptimizations:" << std::endl;
    std::cout << "1) Deterministic Search" << std::endl;
    std::cout << "2) Random Search" << std::endl;
    int opt = 0;
    int method = 0;
    while (opt != 1 && opt != 2) {
        std::cin >> opt;
        switch (opt)
        {
        case 1: {
            method = 1;
            break;}
        case 2: {
            method = 2;
            while (p < 0 || p > 1)
            {
                std::cout << "\nSet p from 0 to 1:";
                std::cin >> p;
            }
            while (delta < 0)
            {
                std::cout << "\nSet delta > 0:";
                std::cin >> delta;
            }
            break; }
        default:
            std::cout << "Error number" << std::endl;
        }
    }

    std::cout << "\nStop Criterions:" << std::endl;
    std::cout << "1) |f(x) - f(y)| < eps" << std::endl;
    std::cout << "2) |x - y| < eps" << std::endl;
    std::cout << "3) n iterations" << std::endl;
    std::cout << "\nSelect Stop Criterion: ";
    int stop;
    StopCriterion* stop_crit = nullptr;
    while (stop_crit == nullptr)
    {
        std::cin >> stop;
        switch (stop) {
        case 1:
            while (eps < 0)
            {
                std::cout << "\nSet eps > 0:";
                std::cin >> eps;
            }
            stop_crit = new StopCriterionByYEps(eps);
            break;
        case 2:
            while (eps < 0)
            {
                std::cout << "\nSet eps > 0:";
                std::cin >> eps;
            }
            stop_crit = new StopCriterionByXEps(eps);
            break;
        case 3:{
            std::cout << "Enter n: ";
            int n = 0;
            std::cin >> n;
            stop_crit = new StopCriterionByN(n);
            break;}
        default:
            std::cout << "Error number" << std::endl;
        }
    }
    std::cout << std::endl;
    std::vector<double> res;
    MultdimOpt* multdim_opt = nullptr;
    switch (method)
    {
    case 1: {
        multdim_opt = new DetermineSearch(*f, r, l, *stop_crit, new TernarySearch(eps));
        break;}
    case 2: {
        multdim_opt = new RandomSearch(*f, r, l, p, delta, *stop_crit);
        break; }
    default:
        break;
    }

    res = multdim_opt->Optimize(x_0);

    std::cout << "\nResult x:" << std::endl; 
    for (int i = 0; i < res.size(); ++i) {
        std::cout << res[i] << " ";
    }
    std::cout << "\nResult f:" << std::endl;
    std::cout << f->operator()(res);

    delete multdim_opt;
    delete stop_crit;
    return 0;
}
