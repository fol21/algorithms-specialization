#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <specialization_algorithms.h>
#include <utils.h>

using namespace std;

int main(int argc, const char** argv) {

    auto raw = getInput("inputs/course1/week3/input_10k.txt");
    // auto raw = vector<int>({3,1,5,4,8,6,7});
    auto arr = vector<int>();
    long int comps = -1;

    cout << "###### Lomuto Quicksort Pivot is First" << "\n";
    arr = vector<int>(raw);
    comps =  Spec_Quicksort_v1::quicksort(&arr);
    cout << "Number of invertions: " << Spec_Algorithms_v1::naiveInvCount(arr) << "\n";
    // _print_vector(arr);
    cout << "Number of comparissons: " << comps << "\n\n";
    
    cout << "###### Lomuto Quicksort Pivot is First with Median" << "\n";
    arr = vector<int>(raw);
    comps =  Spec_Quicksort_v1::quicksort(&arr, LOMUTO, MEDIAN);
    cout << "Number of invertions: " << Spec_Algorithms_v1::naiveInvCount(arr) << "\n";
    // _print_vector(arr);
    cout << "Number of comparissons: " << comps << "\n\n";
    
    cout << "###### Lomuto Quicksort Pivot is Last" << "\n";
    arr = vector<int>(raw);
    comps =  Spec_Quicksort_v1::quicksort(&arr, LOMUTO, LAST);
    cout << "Number of invertions: " << Spec_Algorithms_v1::naiveInvCount(arr) << "\n";
    // _print_vector(arr);
    cout << "Number of comparissons: " << comps << "\n\n";
    
    // cout << "###### Hoare Quicksort" << "\n";
    // arr = vector<int>(raw);
    // comps =  Spec_Quicksort_v1::quicksort(&arr, HOARE);
    // cout << "Number of invertions: " << Spec_Algorithms_v1::naiveInvCount(arr) << "\n";
    // _print_vector(arr);
    // cout << "Number of comparissons: " << comps << "\n\n";
    
    
    return 0;
}