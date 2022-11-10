#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <thread>
#include <mutex>

int main() {
    std::unordered_map<long long, int> hashtable;
    int num = 1000000;
    long long A[num];
    std::ifstream file("inputs/course2/week4/sum2.txt");
    long long in;
    int i = 0;
    while (file >> in) {
        A[i++] = in;
        hashtable[in] = 1;
    }
    int count = 0;
    
    int init = -10000;
    int end = 10000; 
    int left = init;
    int divisor = 12;
    int right = left + (end - init) / divisor;

    std::vector<std::thread> _threads = std::vector<std::thread>(); 
    std::mutex mutex;
    do {
        //threads
        _threads.push_back(std::thread([left, right, &A, &num, &count, &hashtable, &mutex]() {
            for (long long t = left; t <= right; t++) {
                // std::cout << "t is " << t << std::endl;
                for (int i = 0; i < num; i++) {
                    long long y = t-A[i];
                    // std::cout << "y is " << y << std::endl;
                    if (y != A[i]) {
                        if (hashtable.find(y) != hashtable.end()) {
                            const std::lock_guard<std::mutex> lock(mutex);
                            count++;
                            char str[50];
                            std::sprintf(str, "[%d, %d] ", left, right);
                            std::cout << str << "Found " << A[i] << " at position " << i << " and y = " << y << std::endl;
                            break;
                        }
                    }
                }
            }
        }));
        left = right + 1; 
        right = std::min(end, right + (end - init) / divisor);
    }
    while (right < end);

    for (int i=0; i < _threads.size(); i++)
    {
        _threads[i].join();
    }
    
    //for (auto x : A) cout << x << " ";
    // for (long long t = -10000; t <= 10000; t++) {
    //     std::cout << "t is " << t << std::endl;
    //     for (int i = 0; i < num; i++) {
    //         long long y = t-A[i];
    //         // std::cout << "y is " << y << std::endl;
    //         if (y != A[i]) {
    //             if (hashtable.find(y) != hashtable.end()) {
    //                 count++;
    //                 std::cout << "Found " << A[i] << " at position " << i << " and y = " << y << std::endl;
    //                 break;
    //             }
    //         }
            
    //     }
    // }

    std::cout << count;
}