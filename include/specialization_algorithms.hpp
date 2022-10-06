#include <vector>
#include <string>
#include <forward_list>


template<class UniqueIdType = unsigned int>
class Spec_Graph_Vertex_v1
{
    UniqueIdType _id;
    public:
        UniqueIdType Id() {return _id;}

        bool operator==(Spec_Graph_Vertex_v1<UniqueIdType> &obj)
        {
            return obj.Id() == this->_id;
        }
        Spec_Graph_Vertex_v1(UniqueIdType id);
};

template<class UniqueIdType>
Spec_Graph_Vertex_v1<UniqueIdType>::Spec_Graph_Vertex_v1(UniqueIdType id)
{
    this->_id = id;
}