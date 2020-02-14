#include <iostream>
#include "Test.h"

using namespace std;

void GeneratePol(int size, vector<int>& deg, vector<double>& cof)
{
	deg.clear();
	cof.clear();
	for (int i = 0; i < size; i++) {
		int d = rand() % 100;
		double c = (double)(rand() % 100);
		deg.push_back(d);
		cof.push_back(c);
	}
}

int main(int argc, char** argv) 
{
    srand(unsigned(time(0)));
    Test<PolynomialList> test_List;
    Test<PolynomialMap> test_Map;
    vector<int> deg_1, deg_2;
    vector<double> cof_1, cof_2;
    int n = rand() % 4 + 7;

    GeneratePol(n, deg_1, cof_1);
    GeneratePol(n, deg_2, cof_2);
    cout << "Test_List:" << endl;
    test_List.test_construct(deg_1, cof_1);
    test_List.test_operate(deg_1, cof_1, deg_2, cof_2, true);
    cout << "Test_Map: " << endl;
    test_Map.test_construct(deg_1, cof_1);
    test_Map.test_operate(deg_1, cof_1, deg_2, cof_2, true);

    GeneratePol(10*n, deg_1, cof_1);
    GeneratePol(10*n, deg_2, cof_2);
    cout << "Test_List:" << endl;
    test_List.test_construct(deg_1, cof_1);
    test_List.test_operate(deg_1, cof_1, deg_2, cof_2, true);
    cout << "Test_Map: " << endl;
    test_Map.test_construct(deg_1, cof_1);
    test_Map.test_operate(deg_1, cof_1, deg_2, cof_2, true);

    GeneratePol(15*n, deg_1, cof_1);
    GeneratePol(15*n, deg_2, cof_2);
    cout << "Test List:" << endl;
    test_List.test_construct(deg_1, cof_1);
    test_List.test_operate(deg_1, cof_1, deg_2, cof_2, true);
    cout << "Test_Map: " << endl;
    test_Map.test_construct(deg_1, cof_1);
    test_Map.test_operate(deg_1, cof_1, deg_2, cof_2, true);
    return 0;
}
