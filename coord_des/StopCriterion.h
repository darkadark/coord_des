#pragma once
#include <vector>

/**
@brief Класс критериев остановки
*/
class StopCriterion {
public:
    virtual ~StopCriterion() {}
    /**
    @brief Функция необходимости остановки
    @param x координаты точки
    @param y координаты точки
    @param n количество итераций
    */
    virtual bool NeedStop(const std::vector<double>& x, double y, int n) = 0;
};

/**
@brief Класс критерия остановки |f(x) - f(y)| < eps
*/
class StopCriterionByYEps : public StopCriterion {
    double eps; /**< Квадрат эпсилон */
    double y_prev; /**< Координаты точки */
public:
    /**
    @brief Конструктор критерия остановки
    @param eps_ Эпсилон
    */
    StopCriterionByYEps(double eps_) : eps(eps_), y_prev(0) {}
    /**
    @brief Функция необходимости остановки
    @param x координаты точки
    @param y координаты точки
    @param n количество итераций
    */
    bool NeedStop(const std::vector<double>& x, double y, int n) override;
};

/**
@brief Класс критерия остановки |x - y| < eps
*/
class StopCriterionByXEps : public StopCriterion {
    double eps2; /**< Квадрат эпсилон */
    std::vector<double> x_prev; /**< Координаты точки */
public:
    /**
    @brief Конструктор критерия остановки
    @param eps_ Эпсилон
    */
    StopCriterionByXEps(double eps_) : eps2(eps_* eps_) {}
    /**
    @brief Функция необходимости остановки
    @param x координаты точки
    @param y координаты точки
    @param n количество итераций
    */
    bool NeedStop(const std::vector<double>& x, double y, int n) override;
};

/**
@brief Класс критерия остановки n iterations
*/
class StopCriterionByN : public StopCriterion {
    double n_max; /**< Необходимое количество итераций */
public:
    /**
    @brief Конструктор критерия остановки
    @param n_ количество итераций
    */
    StopCriterionByN(double n_) : n_max(n_) {}
    /**
    @brief Функция необходимости остановки
    @param x координаты точки
    @param y координаты точки
    @param n количество итераций
    */
    bool NeedStop(const std::vector<double>& x, double y, int n) override;
};
