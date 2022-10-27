
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <specialization_algorithms.h>
#include <utils.h>

using namespace std;


int main()
{
    vector<int> inputs =  getInput("./inputs/course1/week2/input_100k.txt");
    long unsigned int ans = Spec_Algorithms_v1::mergeSort(&inputs[0], inputs.size());
    cout << " Number of inversions are " << ans << "\n";
    return 0;
}