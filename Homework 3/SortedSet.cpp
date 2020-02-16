//
// Created by terno on 4/7/2019.
//

#include "SortedSet.h"

SortedSet::SortedSet(Relation r) {
    this->r=r;
}

SortedSet::~SortedSet() {
    while(this->set.head!=NULL)
        set.delete_head();
}

/*bool SortedSet::add(TComp e) {
    int pos=this->set.search_by_val(e);
    if (pos!=-1)
        throw Exception;
    else
    {

    }
}*/

bool SortedSet::isEmpty() const {
    if (this->set.head==NULL)
        return true;
    else
        return false;
}

int SortedSet::size() const {
    if (this->set.head==NULL)
        return 0;
    else if (this->set.tail==NULL or this->set.tail==this->set.head)
        return 1;
    else {
        DNode *current=this->set.head;
        int size=0;
        while(current!=NULL)
        {
            size++;
            current=current->next;
        }
        return size;
    }
}

bool SortedSet::search(TElem elem) const {
    if (this->set.search_by_val(elem)!=-1)
        return true;
    else
        return false;
}

SortedSetIterator SortedSet::iterator() const {
    SortedSetIterator it(this->set);
    return it;
}

bool SortedSet::remove(TComp e) {
    return this->set.delete_elem(e);
}

bool SortedSet::add(TComp e) {
    if(this->search(e)) {
        return false;
    }
    else
    {
        if(this->set.head==NULL) {
            this->set.add_head(e);
            return true;
        }
        else
        {
            DNode *current=this->set.head;
            while(!this->r(e, current->info) and current->next!=NULL)
            {
                current=current->next;
            }
            if(current->info==this->set.head->info and this->r(e, this->set.head->info))
            {
                    this->set.add_head(e);
            }
            else if (!this->r(e, current->info))
                this->set.add_tail(e);
            else
            {
                DNode * newNode = new DNode;
                newNode->info=e;
                newNode->prev=current->prev;
                current->prev=newNode;
                newNode->next=current;
                newNode->prev->next=newNode;
            }

            /*
            int e1=1;
            int e2=2;
            if(this->r(e1, e2)) {
                for (int i = e - 1; i >= this->set.head->info; i--) {
                    int x = this->set.search_by_val(i);
                    if (x != -1) {
                        this->set.add_mid(e, x);
                        return true;
                    }
                }
            }
            else{
                for(int i=e+1; i<= this->set.head->info; i++)
                {
                    int x= this->set.search_by_val(i);
                    if(x!=-1){
                        this->set.add_mid(e, x);
                        return true;
                    }
                }
            }
            this->set.add_head(e);
            return true;*/
        }

    }
}


SortedSetIterator::SortedSetIterator(DLL list) {
    Iterator it(list);
    this->iterator=it;
}

void SortedSetIterator::first() {
    this->iterator.first();
}

TElem SortedSetIterator::getCurrent() {
    return this->iterator.get_current();
}

bool SortedSetIterator::valid() {
    return this->iterator.valid();
}

void SortedSetIterator::next() {
    this->iterator.next();
}

/*
 * previous(iterator)
 *      iterator.previous()
 */


void SortedSetIterator::previous() {
    //This function calls the DLL iterator function "previous", which throws an exception if the current element is NULL
    //or changes the current element to the previous one in the set
    //Time complexity: Theta(1)
    this->iterator.previous();
}