#include <iostream>
#include "Matrix.h"

int main() {

    std::ifstream inf("C:\\Users\\romag\\CLionProjects\\OOP1\\mat.txt");
    int n;
    double k;
    inf >> n;
    inf >> k;
    /*Matrix K(n, k);
    Matrix A(n);
    Matrix B(n);
    Matrix C(n);
    Matrix D(n);
    inf >> A;
    inf >> B;
    inf >> C;
    inf >> D;
    C = !C;
    Matrix BC = B * C;
    Matrix AplusBC = A + BC;
    Matrix AplusBCplusK = AplusBC + K;
    D = !D;
    Matrix result = AplusBCplusK * D;*/

    Matrix result(3);
    inf >> result;
    Column result_col(1, result);
    result_col[1] = 100;

    std::cout << result << std::endl << std::endl;

    //std::cout << result(1)[0] << std::endl;
    //result(1)[0] = 42;




    return 0;
}
