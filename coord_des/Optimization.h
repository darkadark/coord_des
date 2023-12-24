/**
@mainpage Покоординатный спуск и случайный поиск
*/
#pragma once

#include <random>
#include "StopCriterion.h"
#include <functional>
#include "Functions.h"

/**
@brief Класс одномерной оптимизации
*/
class OnedimOpt {

public:
    virtual ~OnedimOpt() {}
    /**
    @brief Функция одномерной оптимизации
    @param r правая граница
    @param l левая граница
    @param f функция 
    */
    virtual double Optimize(double r, double l, std::function<double(double)> f) = 0;
};


/**
@brief Класс многомерной оптимизации
*/
class MultdimOpt {
protected:
    const func& f; /**< Функция */
    std::vector<double> r; /**< Правая граница */
    std::vector<double> l; /**< Левая граница */
    StopCriterion& stop_crit; /**< Критерий остановки */
public:
    /**
    @brief Конструктор класса многомерной оптимизации
    @param f_ заданная функция
    @param r_ правая граница
    @param l_ левая граница
    @param stop_crit_ критерий остановки
    */
    MultdimOpt(const func& f_,
        const std::vector<double>& r_,
        const std::vector<double>& l_,
        StopCriterion& stop_crit_) :
        f(f_), r(r_), l(l_), stop_crit(stop_crit_)
    {}
    /**
    @brief Функция многомерной оптимизации
    @param x координаты точки
    */
    virtual std::vector<double> Optimize(const std::vector<double>& x) = 0;
};


/**
@brief Класс метода покоординатного спуска
*/
class DetermineSearch : public MultdimOpt {
    OnedimOpt* onedim_opt; /**< Объект одномерной оптимизации */
public:
    /**
    @brief Конструктор класса метода покоординатного спуска
    @param f_ заданная функция
    @param r_ правая граница
    @param l_ левая граница
    @param stop_crit_ критерий остановки
    @param onedim_opt_ объект одномерной оптимизации
    */
    DetermineSearch(const func& f_,
        const std::vector<double>& r_,
        const std::vector<double>& l_,
        StopCriterion& stop_crit_,
        OnedimOpt* onedim_opt_) :
        MultdimOpt(f_, r_, l_, stop_crit_), onedim_opt(onedim_opt_)
    {}
    ~DetermineSearch() { delete onedim_opt; }
    /**
    @brief Функция многомерной оптимизации методом покоординатного спуска
    @param x координаты точки
    */
    std::vector<double> Optimize(const std::vector<double>& x) override;
};

/**
@brief Класс метода остановки для одномерной оптимизации
*/
class TernarySearch : public OnedimOpt {
    double eps; /**< Эпсилон для остановки */
public:
    /**
    @brief Конструктор класс метода остановки для одномерной оптимизации
    @param eps_ эпсилон для остановки
    */
    TernarySearch(double eps_) : eps(eps_) {}
    /**
    @brief Функция одномерной оптимизации
    @param r правая граница
    @param l левая граница
    @param f функция
    */
    double Optimize(double r, double l, std::function<double(double)> f) override;
};


/**
@brief Класс метода случайного поиска
*/
class RandomSearch : public MultdimOpt {
    std::vector<double> GenY(const std::vector<double>& x); /**< Вектор случайных значений Y */
    std::vector<std::uniform_real_distribution<double>> dist; /**< Вектор границ для генерации случайных значений */
    double p; /**< Вероятность p */
    double delta; /**< Окрестность точки */
public:
    /**
    @brief Конструктор класса метода случайного поиска
    @param f_ заданная функция
    @param r_ правая граница
    @param l_ левая граница
    @param p_ вероятность p
    @param delta_ окрестность точки
    @param stop_crit_ критерий остановки
    */
    RandomSearch(const func& f_,
        const std::vector<double>& r_,
        const std::vector<double>& l_,
        double p_,
        double delta_,
        StopCriterion& stop_crit_) :
        MultdimOpt(f_, r_, l_, stop_crit_), p(p_), delta(delta_)
    {
        dist.reserve(r.size());
        for (int i = 0; i < r.size(); ++i) {
            dist.emplace_back(l[i], r[i]);
        }

    }
    /**
    @brief Функция многомерной оптимизации методом случайного поиска
    @param x координаты точки
    */
    std::vector<double> Optimize(const std::vector<double>& x) override;
};

