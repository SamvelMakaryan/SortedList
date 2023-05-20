#include <iostream>
#include <fstream>
#include "List.hpp"

int main(){
    List<int> values {1, 2, 20, 4, 7, 0, 5, -2, 100, 6, 11, 29};
    std::ofstream fout("output.txt");
    while (!values.empty()) {
        fout << values.pop_front() << " ";
    }
    fout.close();
}