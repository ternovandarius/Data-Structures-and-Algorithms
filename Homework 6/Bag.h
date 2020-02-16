#pragma once



typedef int TElem;
typedef std::pair<TElem, TElem> TPair;
#define NULL_TCOMP 0

class BagIterator;

class Bag {



private:

    /*representation of Bag*/
    int cap=1000;
    int fakesize=0;

    TPair * bag = new TPair[this->cap];


public:
    int realsize=0;
    //constructor

    Bag();



    //adds an element to the bag

    void add(TElem e);



    //removes one occurrence of an element from a bag

    //returns true if an element was removed, false otherwise (if e was not part of the bag)

    bool remove(TElem e);



    //checks if an element appearch is the bag

    bool search(TElem e) const;



    //returns the number of occurrences for an element in the bag

    int nrOccurrences(TElem e) const;



    //returns the number of elements from the bag

    int size() const;



    //returns an iterator for this bag

    BagIterator iterator() const;



    //checks if the bag is empty

    bool isEmpty() const;



    //destructor

    ~Bag();
    TPair* operator[](int pos) const;
    int find_pos(TElem e);
    void print_all(int start_pos);

    TElem mostFrequent() const;
};

class BagIterator{
    friend class Bag;
private:
    const Bag &b;
    TPair * currentElem;
    int count=0;
    int current_count=0;
public:
    BagIterator(const Bag &b);
    void first();
    void next();
    TElem getCurrent();
    bool valid();
};

