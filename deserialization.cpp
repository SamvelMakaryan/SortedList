#include <iostream>
#include <fstream>
#include "List.hpp"

int main(){
    List<int> values;
    std::ifstream fin("output.txt");
    int tmp;
    while (fin >> tmp) {
        values.push_back(tmp);
    }
    std::cout << "values in inserting order" << std::endl;
    values.print();
    std::cout << "values in sorted order" << std::endl;
    values.print_sorted();
    fin.close();
}