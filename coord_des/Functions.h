#pragma once
#include <vector>


/**
@brief Класс заданных функций
*/
class func {
public:
    /**
    @brief Оператор ()
    @param x координаты точки
    */
    virtual double operator()(const std::vector<double>& x) const = 0;
    /**
    @brief Функция, возвращающая размерность заданной функции
    */
    virtual int get_dim() const = 0;
    virtual ~func() {}
};

/**
@brief Класс функции (1 - x)^2 + 100(y - x^2)^2
*/
class f1 : public func {
public:
    /**
    @brief Оператор ()
    @param x координаты точки
    */
    double operator()(const std::vector<double>& x) const override;
    /**
    @brief Функция, возвращающая размерность заданной функции
    */
    int get_dim() const override { return 2; }
};

/**
@brief Класс функции 5x^2 + 6xy + 5y^2
*/
class f2 : public func {
public:
    /**
    @brief Оператор ()
    @param x координаты точки
    */
    double operator()(const std::vector<double>& x) const override;
    int get_dim() const override { return 2; }
};

/**
@brief Класс функции x^2 + y^2 + z^2 + 2x + 2y + 2z
*/
class f3 : public func {
    int dim; /**< Размерность функции */
public:
    f3(int _dim = 3) : dim(_dim) {}
    /**
    @brief Оператор ()
    @param x координаты точки
    */
    double operator()(const std::vector<double>& x) const override;
    /**
    @brief Функция, возвращающая размерность заданной функции
    */
    int get_dim() const override { return dim; }
};
