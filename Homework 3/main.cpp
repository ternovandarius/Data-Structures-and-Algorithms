#include <iostream>
#include "ExtendedTest.cpp"
//#include "ShortTest.cpp"
#include <exception>

bool relation1(TComp e1, TComp e2)
{
    if (e1>=e2)
        return true;
    else
        return false;
}

void test_inlab()
{
    SortedSet *s = new SortedSet(relation1);
    s->add(1);
    s->add(2);
    s->add(3);
    SortedSetIterator i = s->iterator();
    i.first();
    assert (i.getCurrent()==3);
    i.next();
    assert(i.getCurrent()==2);
    i.next();
    assert(i.getCurrent()==1);
    i.previous();
    assert(i.getCurrent()==2);
    i.previous();
    assert(i.getCurrent()==3);
    i.previous();
    assert(i.valid()==false);
    try {
        i.previous();
    }
    catch(std::exception& e)
    {
        std::cout<<1;
    }
}


int main() {
    test_inlab();
    //testAll();
    testAllExtended();
    return 0;
}