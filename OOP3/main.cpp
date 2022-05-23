#include <iostream>
#include "HashMap.h"
#include "Matrix.h"

int main() {

    HashMap<int, int> hashMap(5);
    hashMap.add(1, 10, true);
    hashMap.add(2, 20, true);
    hashMap.add(4, 40, true);
    hashMap.add(55, 50, true);
    hashMap.add(3, 90, true);
    hashMap.add(5, 100, true);
    hashMap.add(9, 100, true);
    HashMap<int, int>::Iterator iterator = hashMap.end();
    hashMap.print_all();


    /*char K, V;
    std::cin >> K >> V;
    int N;
    std::cin >> N;

    if (K == 'I') {
        if (V == 'I') {I_D_S_HashMap<int, int>(N);}
        else if(V == 'D') {I_D_S_HashMap<int, double>(N);}
        else if(V == 'S') {I_D_S_HashMap<int, std::string>(N);}
    }
    else if (K == 'D') {
        if (V == 'I') {I_D_S_HashMap<double, int>(N);}
        else if(V == 'D') {I_D_S_HashMap<double, double>(N);}
        else if(V == 'S') {I_D_S_HashMap<double, std::string>(N);}
    }
    else if (K == 'S') {
        if (V == 'I') {I_D_S_HashMap<std::string , int>(N);}
        else if(V == 'D') {I_D_S_HashMap<std::string, double>(N);}
        else if(V == 'S') {I_D_S_HashMap<std::string, std::string>(N);}
    }*/

    return 0;
}
