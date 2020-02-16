#include <iostream>
#include "ExtendedTest.cpp"

/*
 * 14.ADT  SortedMultiMap–using  a BST with linked  representation  on  an  array.
 * In  the  BST unique keys are stored with a dynamic array of the associated values.
 */

int main() {
    testAll();
    std::cout<<"Passed short tests!\n";
    testAllExtended();
}