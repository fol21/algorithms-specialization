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

std::vector<std::string> split(std::string s, std::string del)
{
    int start, end = -1*del.size();
    std::vector<std::string> _tokens = std::vector<std::string>();
    do {
        start = end + del.size();
        end = s.find(del, start);
        _tokens.push_back(s.substr(start, end - start));
    } while (end != -1);
    return _tokens;
}

bool scontains(std::string str, std::string sub) {
    return str.find(sub) != std::string::npos;
}