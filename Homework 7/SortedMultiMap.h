#pragma once

#include <vector>



typedef int TKey;

typedef int TValue;



#include <utility>

typedef std::pair<TKey, TValue> TElem;




using namespace std;



typedef bool(*Relation)(TKey, TKey);

class DNode{
public:
    TValue *values=new TValue[10];
    int next;
    int prev;
    int realPrev;
    int realNext;
    int size=0;
    int cap=10;
    TKey info;
    DNode(TKey info);
    DNode();
    void add(TValue v);
};

class SMMIterator;

class SortedMultiMap {



private:

    /* representation of the SortedMultiMap */

    int cap;
    int head;
    int tail;
    int firstEmpty;
    Relation r;
    int fakeSize=0;


public:
    int realHead;
    DNode *nodes=new DNode[10];

    // constructor

    SortedMultiMap(Relation r);



    //adds a new key value pair to the sorted multi map

    void add(TKey c, TValue v);



    //returns the values belonging to a given key

    vector<TValue> search(TKey c) const;



    //removes a key value pair from the sorted multimap

    //returns true if the pair was removed (it was part of the multimap), false if nothing is removed

    bool remove(TKey c, TValue v);



    //returns the number of key-value pairs from the sorted multimap

    int size() const;



    //verifies if the sorted multi map is empty

    bool isEmpty() const;



    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	

    SMMIterator iterator();



    // destructor

    ~SortedMultiMap();

};

class SMMIterator{
private:
    SortedMultiMap s;
    int c=0;
    int ci=0;
public:
    SMMIterator(SortedMultiMap &s);
    void first();
    TElem getCurrent();
    bool valid();
    void next();
};

class ValueIterator{
private:
    SortedMultiMap s;
    TKey k;
    vector<TValue> vec;
    int c=0;
public:
    ValueIterator(SortedMultiMap s, TKey k);
    void first();
    TValue getCurrent();
    bool valid();
    void next();
};