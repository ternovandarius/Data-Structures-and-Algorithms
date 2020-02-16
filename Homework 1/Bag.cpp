#include <iostream>
#include <stdexcept>
#include "Bag.h"


typedef int TElem;

Bag::Bag()
    //This function is the constructor for the object Bag.
{   //complexity: Theta(1)
    this->bagSize = 0;
    this->trueSize = 0;
    this->capacity = 100;
    this->elems = new TElem[this->capacity];
    this->frequency = new TElem[this->capacity];
}

void Bag::add(TElem e)
/*
 * This function adds an element to the Bag.
 * Preconditions: b - Bag, e - TElem
 * Input: e
 * Output: -
 * Postconditions: b' = b + {e}
 */
{   //complexity: O(k), where k = nr of unique elems
    int ok = 0;
    int i;
    if(this->trueSize==this->capacity)  //if the size of the bag is equal to the capacity, then we double the capacity
    {
        this->capacity*=2;
        TElem *new_elems=new TElem[this->capacity];
        TElem *new_frequency=new TElem[this->capacity];
        for (i=0; i<this->trueSize; i++)
        {
            new_elems[i]=this->elems[i];
            new_frequency[i]=this->frequency[i];
        }
        delete[] this->elems;
        delete[] this->frequency;
        //for(i=0; i<this->trueSize; i++) {
        elems = new_elems;
        frequency = new_frequency;
        //}
    }
    for (i = 0; i < this->bagSize; i++) //if there is already an existing entry for this element, we just increase the frequency
    {
        if (this->elems[i] == e)
        {
            this->frequency[i]++;
            ok = 1;
            this->bagSize++;
            break;
        }
    }
    if (ok == 0)    //if not, add a new entry for the element
    {
        this->elems[this->trueSize] = e;
        this->frequency[this->trueSize] = 1;
        this->trueSize++;
        this->bagSize++;
    }
}

Bag::~Bag() {
    //This function is the destructor for the object Bag.
    //complexity: O(n^2)
    delete[] this->elems;
    delete[] this->frequency;
}

int Bag::size() const{
    //This function returns the size (number of elements) of the bag.
    //complexity: Theta(1)
    return this->bagSize;
}

bool Bag::isEmpty() const {
    //complexity: Theta(1)
    //This function returns true if the bag is empty, or false otherwise.
    if (this->bagSize == 0)
        return true;
    return false;
}

bool Bag::remove(TElem e){
    /*
     * This function removes an element from the bag.
     * Input: e
     * Preconditions: b - Bag, e - TElem
     * Output: true, if element was removed; false otherwise
     * Postconditions: b' = Bag \ {e}
     */
    //complexity: O(n)
    int i, j;
    for (i=0; i<this->trueSize; i++)
    {
        if (this->elems[i]==e)
        {
            if (this->frequency[i]>1) {     //if the frequency is greater than 1, that means we only need to decrease the frequency by 1
                this->frequency[i]--;
                this->bagSize--;
            }
            else if (i==this->trueSize-1) {     //else, we delete the element completely; this case is for the last element in the Bag
                this->trueSize--;
                this->bagSize--;
            }
            else {                              //this case is for an element on any other position
                for (j=i+1; j<this->trueSize; j++)
                {
                    this->elems[j-1]=this->elems[j];
                }
                this->trueSize--;
                this->bagSize--;
            }
            return true;
        }
    }
    return false;
}

bool Bag::search(TElem e) const{
    /*
     * This function searches for an element in the bag.
     * Input: e
     * Preconditions: b - bag, e - TElem
     * Output: true if element in bag; false otherwise
     * Postconditions: -
     */
    //Complexity: O(n)
    int i;
    for(i=0; i<this->trueSize; i++)
    {
        if (this->elems[i]==e)
            return true;
    }
    return false;
}

int Bag::nrOccurrences(TElem e) const{
    /*
     * This function returns the number of occurrences of an element in the bag.
     * Input: e
     * Preconditions: b - bag, e - TElem
     * Output: nr
     * Postconditions: nr = nr of occurrences
     */
    //Complexity: O(n)
    int i;
    for (i=0; i<this->trueSize; i++)
    {
        if(this->elems[i]==e)
            return this->frequency[i];
    }
    return 0;
}

BagIterator Bag::iterator() const{
    //This function creates and returns a BagIterator object.
    //Complexity: Theta(1)
    return BagIterator(*this);
}

/*TElem Bag::get_elem(int pos) const{
    //This function returns the element at position pos.
    //Complexity: Theta(1)
    return this->elems[pos];
}*/


BagIterator::BagIterator(const Bag &c): con(c)
{
    //This function is the constructor for the object BagIterator.
    //Complexity: Theta(1)
    this->current_position=0;
    this->freq_position=1;
}

void BagIterator::first() {
    //This function sets the BagIterator to the first object in the Bag.
    //Complexity: Theta(1)
    this->current_position=0;
    this->freq_position=1;
}

TElem BagIterator::getCurrent() const {
    //This function returns the current element of the bag.
    //Complexity: Theta(1)
    if (this->valid())
        return this->con.elems[this->current_position];
    else
        throw std::runtime_error("Invalid!");
}

bool BagIterator::valid() const {
    //This function determines whether the current element is valid or not. If the element is the very last one in the bag, it will return false,
    //as we cannot continue with iterating over the bag. If not, it will return true and we can take the next element in the next function. Also, if the
    //bag is empty, it returns false, as it has nothing to iterate over.
    //Complexity: Theta(1)
    if (this->current_position>=this->con.trueSize || this->con.trueSize==0)
        return false;
    return true;
}

void BagIterator::next() {
    //This function relies on the function valid() to determine whether we can continue iterating over the bag, and if so, it takes the next element in the bag.
    //Complexity: Theta(1)
    if (this->valid()==true)
    {
        if (this->freq_position>=this->con.frequency[this->current_position])
        {
            this->current_position++;
            this->freq_position=1;
        }
        else {
            this->freq_position++;
        }
        //std::cout<<this->getCurrent()<<" ";
    }
    else
        throw std::runtime_error("Invalid!");
}

/*
 * previous():
 *
 *      if (current_position == 0 and freq_position ==1) or trueSize==0:
 *          throw "Invalid"
 *      else
 *          if freq_position<=1:
 *              current_position--
 *              freq_position=frequency[current_position]
 *          else
 *              freq_position00
 *          end_if
 *      end_if
 * end_previous
 */

void BagIterator::previous() {
    /* Best: Theta(1)
     * Worst: Theta(1)
     * Average: Theta(1)
     */

    /*
     * This function first determines if the current element is the very first element in the bag, and if so, it throws an exception.
     * If not, it goes to the position before the current element.
     */

    if((this->current_position==0 && this->freq_position==1) || this->con.trueSize==0)
        throw std::runtime_error("Invalid!");
    else
    {
        if (this->freq_position<=1)
        {
            this->current_position--;
            this->freq_position=this->con.frequency[current_position];
        }
        else{
            this->freq_position--;
        }
    }
}