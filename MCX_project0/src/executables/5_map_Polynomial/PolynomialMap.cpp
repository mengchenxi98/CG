#include "PolynomialMap.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

constexpr auto eps = 1.0e-10;

using namespace std;

PolynomialMap::PolynomialMap(const PolynomialMap& other) {
    m_Polynomial = other.m_Polynomial;
}

PolynomialMap::PolynomialMap(const string& file) {
    ReadFromFile(file);
}

PolynomialMap::PolynomialMap(const double* cof, const int* deg, int n) {
    for (int i = 0; i < n; i++)
        coff(deg[i]) = cof[i];
}

PolynomialMap::PolynomialMap(const vector<int>& deg, const vector<double>& cof) {
    assert(deg.size() == cof.size());
    for (size_t i = 0; i < deg.size(); i++)
        coff(deg[i]) = cof[i];
}

double PolynomialMap::coff(int i) const
{
    auto tag = m_Polynomial.find(i);
    if (tag == m_Polynomial.end())
        return 0.;
    return tag->second;
}

double& PolynomialMap::coff(int i) {
    return m_Polynomial[i];
}

void PolynomialMap::compress() {
    map<int, double> tmpPoly = m_Polynomial;
    m_Polynomial.clear();
    for (const auto& term : tmpPoly) {
        if (fabs(term.second) > eps)
            coff(term.first) = term.second;
    }
}

PolynomialMap PolynomialMap::operator+(const PolynomialMap& right) const {
    PolynomialMap poly(right);
    for (const auto& term : m_Polynomial)
        poly.coff(term.first) += term.second;
    poly.compress();
    return poly;
}

PolynomialMap PolynomialMap::operator-(const PolynomialMap& right) const {
    PolynomialMap poly(*this);
    for (const auto& term : right.m_Polynomial)
        poly.coff(term.first) -= term.second;
    poly.compress();
    return poly;
}

PolynomialMap PolynomialMap::operator*(const PolynomialMap& right) const {
    PolynomialMap poly;
    for (const auto& term1 : m_Polynomial) {
        for (const auto& term2 : right.m_Polynomial) {
            int deg = term1.first + term2.first;
            double cof = term1.second * term2.second;
            poly.coff(deg) += cof;
        }
    }
    return poly;
}

PolynomialMap& PolynomialMap::operator=(const PolynomialMap& right) {
    m_Polynomial = right.m_Polynomial;
    return *this;
}

void PolynomialMap::Print() const {
    auto itor = m_Polynomial.begin();
    if (itor == m_Polynomial.end()) {
        cout << "0" << endl;
        return;
    }
    while (itor != m_Polynomial.end()) {
        if (itor != m_Polynomial.begin())
            if (itor->second > 0)
                cout << "+";
        cout << itor->second;
        if (itor->first == 1)
            cout << "x";
        if (itor->first > 1)
            cout << "x^" << itor->first;
        itor++;
    }
    cout << endl;
}

bool PolynomialMap::ReadFromFile(const string& file)
{
    m_Polynomial.clear();
    fstream fl;
    fl.open(file.c_str());
    if (!fl.is_open()) {
        cout << "Can't open file [" << file << "]." << endl;
        return false;
    }
    int len;
    char p;
    fl >> p;
    fl >> len;
    for (int i = 0; i < len; i++) {
        int deg;
        double cof;
        fl >> deg;
        fl >> cof;
        coff(deg) = cof;
    }
    fl.close();
    return true;
}