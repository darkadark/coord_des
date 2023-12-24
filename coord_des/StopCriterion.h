#pragma once
#include <vector>

/**
@brief ����� ��������� ���������
*/
class StopCriterion {
public:
    virtual ~StopCriterion() {}
    /**
    @brief ������� ������������� ���������
    @param x ���������� �����
    @param y ���������� �����
    @param n ���������� ��������
    */
    virtual bool NeedStop(const std::vector<double>& x, double y, int n) = 0;
};

/**
@brief ����� �������� ��������� |f(x) - f(y)| < eps
*/
class StopCriterionByYEps : public StopCriterion {
    double eps; /**< ������� ������� */
    double y_prev; /**< ���������� ����� */
public:
    /**
    @brief ����������� �������� ���������
    @param eps_ �������
    */
    StopCriterionByYEps(double eps_) : eps(eps_), y_prev(0) {}
    /**
    @brief ������� ������������� ���������
    @param x ���������� �����
    @param y ���������� �����
    @param n ���������� ��������
    */
    bool NeedStop(const std::vector<double>& x, double y, int n) override;
};

/**
@brief ����� �������� ��������� |x - y| < eps
*/
class StopCriterionByXEps : public StopCriterion {
    double eps2; /**< ������� ������� */
    std::vector<double> x_prev; /**< ���������� ����� */
public:
    /**
    @brief ����������� �������� ���������
    @param eps_ �������
    */
    StopCriterionByXEps(double eps_) : eps2(eps_* eps_) {}
    /**
    @brief ������� ������������� ���������
    @param x ���������� �����
    @param y ���������� �����
    @param n ���������� ��������
    */
    bool NeedStop(const std::vector<double>& x, double y, int n) override;
};

/**
@brief ����� �������� ��������� n iterations
*/
class StopCriterionByN : public StopCriterion {
    double n_max; /**< ����������� ���������� �������� */
public:
    /**
    @brief ����������� �������� ���������
    @param n_ ���������� ��������
    */
    StopCriterionByN(double n_) : n_max(n_) {}
    /**
    @brief ������� ������������� ���������
    @param x ���������� �����
    @param y ���������� �����
    @param n ���������� ��������
    */
    bool NeedStop(const std::vector<double>& x, double y, int n) override;
};
