#pragma once
#include "DLL.cpp"


typedef int TElem;

typedef TElem TComp;



typedef bool (*Relation)(TComp, TComp);

class SortedSetIterator;

class SortedSet {
    friend class SortedSetIterator;
private:
	/*Representation of the SortedSet*/
    DLL set;
    Relation r;
public:

	//constructor

	SortedSet(Relation r);



	//adds an element to the sorted set

	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 

	//it returns false

	bool add(TComp e);



	

	//removes an element from the sorted set

	//if the element was removed, it returns true, otherwise false

	bool remove(TComp e);



	//checks if an element is in the sorted set

	bool search(TElem elem) const;





	//returns the number of elements from the sorted set

	int size() const;



	//checks if the sorted set is empty

	bool isEmpty() const;



	//returns an iterator for the sorted set

	SortedSetIterator iterator() const;



	// destructor

	~SortedSet();





};


class SortedSetIterator{
    friend class SortedSet;
private:
    Iterator iterator;
    SortedSetIterator(DLL list);
public:
    void first();
    TElem getCurrent();
    bool valid();
    void next();
    void previous();
};