//
// Created by terno on 5/11/2019.
//

#include "Bag.h"
#include <exception>

Bag::Bag() {
    this->cap=1000;
    this->fakesize=0; //number of numbers in bag
    this->realsize=0; //number of keys in hashtable
    TPair t(NULL, NULL);
    TPair * bag1=new TPair[this->cap];
    this->bag=bag1;
}

int Bag::size() const {
    return this->fakesize;
}

bool Bag::isEmpty() const {
    if(this->fakesize==0)
        return true;
    else
        return false;
}

bool Bag::search(TElem e) const {
    if (this->realsize==0)
        return false;
    for(int i=0; i<this->cap; i++)
    {
        if(this->bag[i].first==e)
            return true;
    }
    return false;
}

Bag::~Bag() {
    delete[] this->bag;
}

int Bag::nrOccurrences(TElem e) const {
    if(this->realsize==0)
        return 0;
    for(int i=0; i<this->cap; i++)
    {
        if(this->bag[i].first==e)
            return this->bag[i].second;
    }
    return 0;
}

void Bag::add(TElem e) {
    TElem result;
    //if(this->realsize!=0) {
        result = this->find_pos(e);
        if (result != -1) {
            this->bag[result].second++;
            this->fakesize++;
        } else {
            if (this->realsize == this->cap/2) {
                TPair *newBag = new TPair[this->cap*2];
                for(int j=0; j<this->cap*2; j++)
                    newBag[j].first=NULL;
                for (int i = 0; i < this->cap/2; i++) {
                    int pos;
                    int k = 0;
                    pos = this->bag[i].first % this->cap;
                    int newPos=pos;
                    if (pos<0)
                        newPos=abs(pos);
                    while (newBag[pos].first != NULL) {
                        k++;
                        newPos = (abs(this->bag[i].first) + k * k) % this->cap;
                    }
                    newBag[newPos].first = this->bag[i].first;
                    newBag[newPos].second = this->bag[i].second;
                }
                delete[] this->bag;
                this->bag = newBag;
                this->cap *= 2;
            }
            int k = 0;
            int pos;
            int val=e;
            if(e<0)
                val=abs(e);
            pos = val % this->cap;
            while (this->bag[pos].first != NULL) {
                k++;
                pos = (val + k * k) % this->cap;
            }
            /*if (this->bag[pos].first!=NULL)
            {
                for(int i=0; i<this->realsize; i++)
                    if(this->bag[i].first==NULL)
                    {
                        pos=i;
                        break;
                    }
            }*/
            TElem elem = e;
            this->bag[pos].first = elem;
            this->bag[pos].second = 1;
            this->realsize++;
            this->fakesize++;
        }
    /*}
    else
    {
        this->bag[0].first=e;
        this->bag[0].second=1;
        this->realsize++;
        this->fakesize++;
    }*/
}

bool Bag::remove(TElem e) {
    if(this->realsize==0)
        return false;
    TElem result;
    result=this->find_pos(e);
    if(result==-1)
    {
        return false;
    }
    else{
        if(this->bag[result].second==1)
        {
            this->bag[result].first=NULL;
            this->bag[result].second=NULL;
            this->fakesize--;
            this->realsize--;
        }
        else {
            this->bag[result].second--;
            this->fakesize--;
        }
        return true;
    }
}

TPair* Bag::operator[](int pos) const {
    return &this->bag[pos];
}

BagIterator::BagIterator(const Bag &b): b(b) {
    this->currentElem=this->b[0];
    this->count=0;
    this->current_count=1;
}

void BagIterator::first() {
    this->currentElem=b[0];
    this->count=0;
    this->current_count=1;
}

TElem BagIterator::getCurrent() {
    return this->currentElem->first;
}

bool BagIterator::valid() {
    if((this->current_count==this->currentElem->second and this->count==this->b.realsize) or this->currentElem->first==NULL)
        return false;
    return true;
}

void BagIterator::next() {
    if(this->valid())
    {
        if(this->currentElem->second==this->current_count)
        {
            this->count++;
            this->current_count=1;
            this->currentElem->first=this->b[this->count]->first;
            this->currentElem->second=this->b[this->count]->second;
        }
        else
            this->current_count++;
    }
}

BagIterator Bag::iterator() const {
    return BagIterator (*this);
}

int Bag::find_pos(TElem e) {
    int val=e;
    if(e<0)
        val=abs(e);
    int pos=abs(val)%this->cap;
    int i=0;
    while (this->bag[pos].first!=e and i<this->cap)
    {
        i++;
        pos=(val+i*i)%this->cap;
    }
    if(this->bag[pos].first==e)
        return pos;
    else
        return -1;
}

void Bag::print_all(int start_pos) {
    for(int i=start_pos; i<this->cap;i++)
    {
        if(this->bag[i].first!=NULL)
            std::cout<<"<"<<this->bag[i].first<<","<<this->bag[i].second<<">";
        else
            std::cout<<"<NIL, NIL>";
    }
}

//O(this->cap)
TElem Bag::mostFrequent() const {
    if(this->realsize==0)
        return NULL_TCOMP;
    TElem max_elem;
    int max_freq=0;
    for(int i=0; i<this->cap; i++)
    {
        if(this->bag[i].second>max_freq)
        {
            max_elem=this->bag[i].first;
            max_freq=this->bag[i].second;
        }
    }
    return max_elem;
}

/* #define NULL_TCOMP 0
 *
 * subalg mostFrequent(Bag b)
 *     if b->realsize==0 then
 *          mostFrequent<-NULL_TCOMP
 *     end_if
 *     max_elem:TElem
 *     max_freq=0:int
 *     for int i<-0, b->cap do
 *          if b->bag[i]->second>max_freq then
 *              max_elem<-b->bag[i].first
 *              max_freq<-b->bag[i].second
 *          end_if
 *     end_for
 *     mostFrequent<-max_elem
 * end_subalg
 */