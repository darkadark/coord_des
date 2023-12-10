// coord_des.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include "Optimization.h"
#include "Functions.h"



int main()
{
    double eps = 1e-06;
    
    std::cout << "COORDINATE DESCENT" << std::endl;
    std::cout << "\nFunctions:" << std::endl;
    std::cout << "1) (1 - x)^2 + 100(y - x^2)^2" << std::endl;
    std::cout << "2) 5x^2 + 6xy + 5y^2"<< std::endl;
    std::cout << "3) x^2 + y^2 + z^2 + 2x + 2y + 2z" << std::endl;
    std::cout << "Select function: ";
    int func;
    std::cin >> func;
    std::function<double(const std::vector<double>&)> f;
    double dim;
    switch (func) {
    case 1: 
        dim = 2;
        f = f1;
        break;
    case 2:
        dim = 2;
        f = f2;
        break;
    case 3: 
        dim = 3;
        f = f3;
        break;

    }
    std::cout << std::endl;
    std::vector<double> x_0(dim);
    std::cout << "Enter starting point" << std::endl;
    double xi;
    for (int i = 0; i < dim; ++i) {
        std::cout << "Coordinate " << i+1 <<": ";
        std::cin >> xi;
        x_0[i] = xi;
    }
    //std::vector<double> x_0{ 0.5, 0.5 };
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
            stop_crit = new StopCriterionByYEps(eps);
            break;
        case 2:
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
    switch (method)
    {
    case 1: {
        TernarySearch ternary_search(eps);
        //StopCriterionByYEps stop_crit(eps);
        DetermineSearch determine_opt(f, r, l, *stop_crit, ternary_search);
        res = determine_opt.Optimize(x_0);
        break;}
    case 2: {
        //StopCriterionByN stop_crit_n(100);
        RandomSearch random_opt(f, r, l, *stop_crit);
        res = random_opt.Optimize(x_0);
        break; }
    default:
        break;
    }

    std::cout << "\nResult:" << std::endl; 
    for (int i = 0; i < res.size(); ++i) {
        std::cout << res[i] << " ";
    }
    
    delete stop_crit;

    return 0;
}
