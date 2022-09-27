#include <utils.h>

using namespace std;

vector<int> getInput(string path)
{
    vector<int> inputs = vector<int>();

    ifstream file;
    file.open(path);

    string line;
    if ( file.is_open() ) {
        while ( getline(file, line)) {
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