#pragma once


typedef int TElem;

class BagIterator;

class Bag {

	friend class BagIterator;

private:

	/*representation of Bag*/
	TElem *elems;
	TElem *frequency;
	int bagSize;
	int trueSize;
	int capacity;


public:

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

	//TElem get_elem(int pos) const;
};

class BagIterator {
    friend class Bag;
private:

    //Constructor receives a reference of the container.

    //after creation the iterator will refer to the first element of the container, or it will be invalid if the container is empty



    //contains a reference of the container it iterates over

    const Bag &con;


    /* representation specific for the iterator*/
    int current_position;
    int freq_position;



public:

    BagIterator(const Bag &c);

    //sets the iterator to the first element of the container

    void first();



    //moves the iterator to the next element

    //throws exception if the iterator is not valid

    void next();

    void previous();


    //checks if the iterator is valid

    bool valid() const;



    //returns the value of the current element from the iterator

    // throws exception if the iterator is not valid

    TElem getCurrent() const;



};