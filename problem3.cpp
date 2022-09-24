#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include<mutex>
#include <math.h>
#include <sys/time.h>
#include <time.h>

#include <specialization_algorithms.h>


#define __LEN_INT__(X) sizeof(X) / sizeof(X[0])

using namespace std;

int partition(vector<int>* arr, int low, int high, int* comps);
void quicksort(vector<int>* arr, int low, int high, int* comps);
int quicksort(vector<int>* arr);

template<class T>
void swap(vector<T>* arr, int idx1, int idx2);

vector<int> getInput(string path)
{
    vector<int> inputs = vector<int>();

    ifstream file;
    file.open(path);

    string line;
    if ( file.is_open() ) {
        while ( file ) {
            getline(file, line);
            inputs.push_back(atoi(line.c_str()));
        }
    }
    file.close();
    return inputs;
}

void _print_vector(vector<int> vec)
{
    cout << "Sorted: [ ";
    for (auto i: vec)
        cout << i << ", ";
    cout << "]\n";
}

int main(int argc, const char** argv) {

    auto raw = getInput("inputs/input_10k.txt");
    // auto arr = vector<int>({3,1,5,4,8,6,7});
    // int comps =  Spec_Quicksort_v1::quicksort(&arr, HOARE);
    auto arr = vector<int>();
    long int comps = -1;
    cout << "###### Lomuto Quicksort Pivot is First" << "\n";
    arr = vector<int>(raw);
    comps =  Spec_Quicksort_v1::quicksort(&arr);
    cout << "Number of invertions: " << Spec_Algorithms_v1::naiveInvCount(arr) << "\n";
    cout << "Number of comparissons: " << comps << "\n\n";
    
    cout << "###### Lomuto Quicksort Pivot is First with Median" << "\n";
    arr = vector<int>(raw);
    comps =  Spec_Quicksort_v1::quicksort(&arr, LOMUTO, FIRST_MEDIAN);
    cout << "Number of invertions: " << Spec_Algorithms_v1::naiveInvCount(arr) << "\n";
    cout << "Number of comparissons: " << comps << "\n\n";
    
    cout << "###### Lomuto Quicksort Pivot is Last" << "\n";
    arr = vector<int>(raw);
    comps =  Spec_Quicksort_v1::quicksort(&arr, LOMUTO, LAST);
    cout << "Number of invertions: " << Spec_Algorithms_v1::naiveInvCount(arr) << "\n";
    cout << "Number of comparissons: " << comps << "\n\n";
    
    cout << "###### Lomuto Quicksort Pivot is Last with Median" << "\n";
    arr = vector<int>(raw);
    comps =  Spec_Quicksort_v1::quicksort(&arr, LOMUTO, LAST_MEDIAN);
    cout << "Number of invertions: " << Spec_Algorithms_v1::naiveInvCount(arr) << "\n";
    cout << "Number of comparissons: " << comps << "\n\n";
    
    cout << "###### Hoare Quicksort" << "\n";
    arr = vector<int>(raw);
    comps =  Spec_Quicksort_v1::quicksort(&arr, HOARE);
    cout << "Number of invertions: " << Spec_Algorithms_v1::naiveInvCount(arr) << "\n";
    cout << "Number of comparissons: " << comps << "\n\n";
    
    //  _print_vector(arr);
    return 0;
}