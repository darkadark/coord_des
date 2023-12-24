/**
@mainpage �������������� ����� � ��������� �����
*/
#pragma once

#include <random>
#include "StopCriterion.h"
#include <functional>
#include "Functions.h"

/**
@brief ����� ���������� �����������
*/
class OnedimOpt {

public:
    virtual ~OnedimOpt() {}
    /**
    @brief ������� ���������� �����������
    @param r ������ �������
    @param l ����� �������
    @param f ������� 
    */
    virtual double Optimize(double r, double l, std::function<double(double)> f) = 0;
};


/**
@brief ����� ����������� �����������
*/
class MultdimOpt {
protected:
    const func& f; /**< ������� */
    std::vector<double> r; /**< ������ ������� */
    std::vector<double> l; /**< ����� ������� */
    StopCriterion& stop_crit; /**< �������� ��������� */
public:
    /**
    @brief ����������� ������ ����������� �����������
    @param f_ �������� �������
    @param r_ ������ �������
    @param l_ ����� �������
    @param stop_crit_ �������� ���������
    */
    MultdimOpt(const func& f_,
        const std::vector<double>& r_,
        const std::vector<double>& l_,
        StopCriterion& stop_crit_) :
        f(f_), r(r_), l(l_), stop_crit(stop_crit_)
    {}
    /**
    @brief ������� ����������� �����������
    @param x ���������� �����
    */
    virtual std::vector<double> Optimize(const std::vector<double>& x) = 0;
};


/**
@brief ����� ������ ��������������� ������
*/
class DetermineSearch : public MultdimOpt {
    OnedimOpt* onedim_opt; /**< ������ ���������� ����������� */
public:
    /**
    @brief ����������� ������ ������ ��������������� ������
    @param f_ �������� �������
    @param r_ ������ �������
    @param l_ ����� �������
    @param stop_crit_ �������� ���������
    @param onedim_opt_ ������ ���������� �����������
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
    @brief ������� ����������� ����������� ������� ��������������� ������
    @param x ���������� �����
    */
    std::vector<double> Optimize(const std::vector<double>& x) override;
};

/**
@brief ����� ������ ��������� ��� ���������� �����������
*/
class TernarySearch : public OnedimOpt {
    double eps; /**< ������� ��� ��������� */
public:
    /**
    @brief ����������� ����� ������ ��������� ��� ���������� �����������
    @param eps_ ������� ��� ���������
    */
    TernarySearch(double eps_) : eps(eps_) {}
    /**
    @brief ������� ���������� �����������
    @param r ������ �������
    @param l ����� �������
    @param f �������
    */
    double Optimize(double r, double l, std::function<double(double)> f) override;
};


/**
@brief ����� ������ ���������� ������
*/
class RandomSearch : public MultdimOpt {
    std::vector<double> GenY(const std::vector<double>& x); /**< ������ ��������� �������� Y */
    std::vector<std::uniform_real_distribution<double>> dist; /**< ������ ������ ��� ��������� ��������� �������� */
    double p; /**< ����������� p */
    double delta; /**< ����������� ����� */
public:
    /**
    @brief ����������� ������ ������ ���������� ������
    @param f_ �������� �������
    @param r_ ������ �������
    @param l_ ����� �������
    @param p_ ����������� p
    @param delta_ ����������� �����
    @param stop_crit_ �������� ���������
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
    @brief ������� ����������� ����������� ������� ���������� ������
    @param x ���������� �����
    */
    std::vector<double> Optimize(const std::vector<double>& x) override;
};

