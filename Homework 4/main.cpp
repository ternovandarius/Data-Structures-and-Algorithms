#include <iostream>
#include "ShortTest.cpp"
#include "ExtendedTest.cpp"
#include <assert.h>

//Problem 16

void test_MM(){
    MultiMap m;
    assert(m.isEmpty());
    std::cout<<m.size()<<std::endl;
    m.add(1, 2);
    std::cout<<m.size()<<std::endl;
    m.add(1, 4);
    std::cout<<m.size()<<std::endl;
    m.add(2, 4);
    std::cout<<m.size()<<std::endl;
    m.add(4, 4);
    m.add(2, 14);
    std::cout<<m.size()<<std::endl;
    m.remove(4, 4);
    std::cout<<m.size()<<std::endl;
    m.remove(2, 4);
    std::cout<<m.size()<<std::endl;
    std::cout<<"Search:"<<std::endl;
    std::vector<TValue> vec=m.search(2);
    for(int i=0; i<vec.size(); i++)
        std::cout<<vec[i]<<" ";
    /*std::cout<<"Iterator:"<<std::endl;
    MultiMapIterator i(m);
    i.first();
    while(i.valid())
    {
        TElem e=i.getCurrent();
        std::cout<<"("<<e.first<<", "<<e.second<<") ";
        i.next();
    }*/
}

int main() {
    //test_MM();
    //testAll();
    testAllExtended();
    return 0;
}