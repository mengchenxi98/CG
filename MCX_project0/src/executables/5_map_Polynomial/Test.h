#include "PolynomialList.h"
#include "PolynomialMap.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

template<class Polynomial>
class Test {
public:
    bool test_construct(const vector<int>& deg, const vector<double>& cof) {
        clock_t t0 = clock();
        cout << "Size: " << deg.size() << endl;
        Polynomial p(deg, cof);
        cout << "Construct_time: " << clock() - t0 << endl << endl;
        return true;
    }
    bool test_operate(const vector<int>& deg_1, const vector<double>& cof_1,
        const vector<int>& deg_2, const vector<double>& cof_2, bool showOutput = false)
    {
        Polynomial p_1(deg_1, cof_1);
        Polynomial p_2(deg_2, cof_2);
        clock_t t0 = clock();
        if (showOutput) {
            (p_1 * p_2).Print();
            (p_1 + p_2).Print();
            (p_1 - p_2).Print();
        }
        else {
            p_1 * p_2;
            p_1 + p_2;
            p_1 - p_2;
        }
        cout << "Operate_time: " << clock() - t0 << endl << endl;
        return true;
    }
};