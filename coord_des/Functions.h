#pragma once
#include <vector>


/**
@brief ����� �������� �������
*/
class func {
public:
    /**
    @brief �������� ()
    @param x ���������� �����
    */
    virtual double operator()(const std::vector<double>& x) const = 0;
    /**
    @brief �������, ������������ ����������� �������� �������
    */
    virtual int get_dim() const = 0;
    virtual ~func() {}
};

/**
@brief ����� ������� (1 - x)^2 + 100(y - x^2)^2
*/
class f1 : public func {
public:
    /**
    @brief �������� ()
    @param x ���������� �����
    */
    double operator()(const std::vector<double>& x) const override;
    /**
    @brief �������, ������������ ����������� �������� �������
    */
    int get_dim() const override { return 2; }
};

/**
@brief ����� ������� 5x^2 + 6xy + 5y^2
*/
class f2 : public func {
public:
    /**
    @brief �������� ()
    @param x ���������� �����
    */
    double operator()(const std::vector<double>& x) const override;
    int get_dim() const override { return 2; }
};

/**
@brief ����� ������� x^2 + y^2 + z^2 + 2x + 2y + 2z
*/
class f3 : public func {
    int dim; /**< ����������� ������� */
public:
    f3(int _dim = 3) : dim(_dim) {}
    /**
    @brief �������� ()
    @param x ���������� �����
    */
    double operator()(const std::vector<double>& x) const override;
    /**
    @brief �������, ������������ ����������� �������� �������
    */
    int get_dim() const override { return dim; }
};
