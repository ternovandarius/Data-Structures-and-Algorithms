#pragma once

#include "DLLA.cpp"

#include<vector>

#include<utility>



using namespace std;


typedef int TKey;

typedef int TValue;



typedef std::pair<TKey, TValue> TElem;

class MultiMapIterator;

class MultiMap

{



private:

    /* representation of the MultiMap */



public:
    DLLA * d;
    //constructor

    MultiMap();



    //adds a key value pair to the multimap

    void add(TKey c, TValue v);



    //removes a key value pair from the multimap

    //returns true if the pair was removed (if it was in the multimap) and false otherwise

    bool remove(TKey c, TValue v);



    //returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty

    vector<TValue> search(TKey c) const;



    //returns the number of pairs from the multimap

    int size();



    //checks whether the multimap is empty

    bool isEmpty() const;



    //returns an iterator for the multimap

    MultiMapIterator iterator();



    //descturctor

    ~MultiMap();





};


class MultiMapIterator{
    friend class DLLA;
    friend class DLLAIterator;
private:
    MultiMap m;
    int c=0;
    int ci=0;
public:
    MultiMapIterator(MultiMap &m);
    void first();
    TElem getCurrent();
    bool valid();
    void next();
};
