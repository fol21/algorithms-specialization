#include <iostream>

#include <specialization_algorithms.h>
#include <utils.h>


int main(int argc, const char** argv) {

    Spec_Graph_Vertex_v1<int> v1(1);
    Spec_Graph_Vertex_v1<int> v2(2);
    Spec_Graph_Vertex_v1<int> v3(3);

    if(v1 == (int)1)
    {
        cout << "Equals" << endl;
    }
    return 0;
}