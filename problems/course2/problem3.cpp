// C++ program for implementation of Heap Sort

#include <iostream>
#include <queue>
#include <numeric>
#include <math.h>

#include <specialization_algorithms.h>
using namespace std;

queue<int> bufferInput(string path)
{
    queue<int> inputs = queue<int>();

    ifstream file;
    file.open(path);

    string line;
    if ( file.is_open() ) {
        while ( getline(file, line)) {
            inputs.push(atoi(line.c_str()));
        }
    }
    file.close();
    return inputs;
}

// A utility function to print array of size n
void printArray(int arr[], int N)
{
	for (int i = 0; i < N; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}

// Driver's code
int main()
{
	int arr[] = { 12, 11, 13, 5, 6, 7 };
	int N = sizeof(arr) / sizeof(arr[0]);

    auto inputs = bufferInput("inputs/course2/week3/median.txt");
    auto sequence = vector<int>();
    auto medians = vector<int>();

    while(!inputs.empty())
    {
        sequence.push_back(inputs.front());
        inputs.pop();
	    Spec_Heapsort_v1::heapSort(&sequence);
        // cout << "Sorted array is: "; printArray(sequence.data(), sequence.size());

        int _adj = sequence.size() % 2 == 0 ? 1 : 0;
        int _index = sequence.size() == 1 ? 0 : floor(sequence.size()/2) - _adj;
        medians.push_back(sequence[_index]);
    }
    cout << medians.size() << endl;
	cout << std::accumulate(medians.data(), medians.data()+medians.size(), 0) << endl;
	cout << std::accumulate(medians.data(), medians.data()+medians.size(), 0) % medians.size() << endl;
}
