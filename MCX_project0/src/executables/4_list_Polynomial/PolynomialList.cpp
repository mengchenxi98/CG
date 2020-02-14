#include "PolynomialList.h"
#include <iostream>
#include <fstream>
#include <assert.h>

#include <algorithm>
#include <cmath>
constexpr auto eps = 1.0e-10;

using namespace std;

PolynomialList::PolynomialList(const PolynomialList& other) {
    m_Polynomial = other.m_Polynomial;
}

PolynomialList::PolynomialList(const string& file) {
    ReadFromFile(file);
}

PolynomialList::PolynomialList(const double* cof, const int* deg, int n) {
    for (int i = 0; i < n; i++) {
        const Term temp(deg[i], cof[i]);
        AddOneTerm(temp);
    }
}

PolynomialList::PolynomialList(const vector<int>& deg, const vector<double>& cof) {
    assert(deg.size() == cof.size());
    for (size_t i = 0; i < deg.size(); i++)
        AddOneTerm(Term(deg[i], cof[i]));
}

double PolynomialList::coff(int i) const {
    auto itor = m_Polynomial.begin();
    while (itor != m_Polynomial.end()) {
        if (i > (*itor).deg)
            break;
        if (i == (*itor).deg)
            return (*itor).cof;
        itor++;
    }
    return 0.;
}

double& PolynomialList::coff(int i) {
    return AddOneTerm(Term(i, 0)).cof;
}

void PolynomialList::compress() {
    auto itor = m_Polynomial.begin();
    while (itor != m_Polynomial.end()) {
        if (fabs((*itor).cof) < eps)
            itor = m_Polynomial.erase(itor);
        else
            itor++;
    }
}

PolynomialList PolynomialList::operator+(const PolynomialList& right) const {
    PolynomialList temp(right);
    auto itor = m_Polynomial.begin();
    while (itor != m_Polynomial.end()) {
        temp.AddOneTerm(*itor);
        itor++;
    }
    temp.compress();
    return temp;
}

PolynomialList PolynomialList::operator-(const PolynomialList& right) const {
    PolynomialList temp(*this);
    auto itor = right.m_Polynomial.begin();
    while (itor != right.m_Polynomial.end()) {
        temp.AddOneTerm(Term((*itor).deg, -(*itor).cof));
        itor++;
    }
    temp.compress();
    return temp;
}

PolynomialList PolynomialList::operator*(const PolynomialList& right) const {
    PolynomialList F;
    auto itor1 = right.m_Polynomial.begin();
    auto itor2 = m_Polynomial.begin();
    while (itor1 != right.m_Polynomial.end()) {
        while (itor2 != m_Polynomial.end()) {
            const Term temp((*itor1).deg + (*itor2).deg, (*itor1).cof * (*itor2).cof);
            F.AddOneTerm(temp);
            itor2++;
        }
        itor1++;
        itor2 = m_Polynomial.begin();
    }
    F.compress();
    return F;
}

PolynomialList& PolynomialList::operator=(const PolynomialList& right) {
    m_Polynomial = right.m_Polynomial;
    return *this;
}

void PolynomialList::Print() const {
    auto itor = m_Polynomial.begin();
    if (itor == m_Polynomial.end()) {
        cout << "0" << endl;
        return;
    }
    while (itor != m_Polynomial.end()) {
        if (itor != m_Polynomial.begin())
            if ((*itor).cof > 0)
                cout << "+";
        cout << (*itor).cof;
        if ((*itor).deg == 1)
            cout << "x";
        if ((*itor).deg > 1)
            cout << "x^" << (*itor).deg;
        itor++;
    }
    cout << endl;
}

bool PolynomialList::ReadFromFile(const string& file) {
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
        Term temp;
        fl >> temp.deg;
        fl >> temp.cof;
        AddOneTerm(temp);
    }
    fl.close();
    return true;
}

PolynomialList::Term& PolynomialList::AddOneTerm(const Term& term) {
    auto itor = m_Polynomial.begin();
    while (itor != m_Polynomial.end()) {
        if (term.deg > (*itor).deg) {
            itor = m_Polynomial.insert(itor, term);
            break;
        }
        if (term.deg == (*itor).deg) {
            (*itor).cof += term.cof;
            break;
        }
        itor++;
    }
    if (itor == m_Polynomial.end())
        itor = m_Polynomial.insert(itor, term);
    return *itor;
}