#if !defined(UTILS_H)
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <sys/time.h>
#include <time.h>

std::vector<int> getInput(std::string path);

std::vector<std::string> split(std::string s, std::string del = " ");

bool scontains(std::string str, std::string sub);

template<typename T>
void print_vector(std::vector<T> vec)
{
    std::cout << "[ ";
    for (auto i: vec)
        std::cout << i << ", ";
    std::cout << "]\n";
}

#endif // UTILS_H
