//
// Created by terno on 4/7/2019.
//

#include "DLL.h"
#include <exception>
#include <assert.h>
#include <stdexcept>

DNode::DNode() {
    this->info=0;
    this->next=NULL;
    this->prev=NULL;
}

DNode::DNode(TElem info) {
    this->info=info;
    this->prev=NULL;
    this->next=NULL;
}

void DLL::add_head(TElem elem) {
    DNode *node = new DNode;
    node->info=elem;
    if (this->head==NULL) {
        this->head = node;
        this->tail = node;
    }
    else
    {
        node->next=this->head;
        this->head->prev=node;
        this->head=node;
    }
};

void DLL::add_tail(TElem elem) {
    DNode *node = new DNode;
    node->info=elem;
    if (this->head==NULL) {
        this->head = node;
        this->tail = node;
    }
    else if(this->tail==NULL)
        this->tail=node;
    else
    {
        node->prev=this->tail;
        this->tail->next=node;
        this->tail=node;
    }
}

bool DLL::add_mid(TElem elem, int pos) {
    if (pos<0)
        return false;
    /*else if (pos==0) {
        this->add_head(elem);
        return true;
    }*/
    else
    {
        DNode *current;
        int currentPos=0;
        current=this->head;
        while (current!=NULL and currentPos<pos)
        {
            DNode *next=current->next;
            current=next;
            currentPos++;
        }
        if (current==NULL || current->info==this->tail->info) {
            this->add_tail(elem);
            return true;
        }
        else {
            DNode *node = new DNode;
            node->info=elem;
            node->prev=current->next->prev;
            current->next->prev=node;
            node->next=current->next;
            current->next=node;
            return true;
        }
    }
}

TElem DLL::search_by_val(int val) const {
    DNode *current;
    int currentPos=0;
    current=this->head;
    while(current!=NULL and current->info!=val)
    {
        DNode *next=current->next;
        current=next;
        currentPos++;
    }
    if (current==NULL)
        return -1;
    return currentPos;
}

TElem DLL::search_by_pos(int pos) {
    DNode *current;
    int currentPos=0;
    current=this->head;
    while(current!=NULL and currentPos<pos)
    {
        DNode *next=current->next;
        current=next;
        currentPos++;
    }
    return current->info;
}

void DLL::delete_head() {
    DNode *oldHead = this->head;
    DNode *second = this->head->next;
    if (second!=NULL) {
        second->prev = NULL;
        this->head = second;
    }
    else
    {
        if (this->head == this->tail)
            this->tail = NULL;
        this->head = NULL;
    }
}

void DLL::delete_last() {
    DNode *oldTail = this->tail;
    DNode *second_to_last = this->tail->prev;
    if (second_to_last!=NULL) {
        second_to_last->next = NULL;
        this->tail = second_to_last;
    }
    else{
        if (this->tail==this->head)
            this->head=NULL;
        this->tail=NULL;
    }
}

bool DLL::delete_elem(TElem elem) {
    DNode *current = this->head;
    while (current!=NULL and current->info!=elem)
    {
        current=current->next;
    }
    if (current!=NULL)
    {
        if(current==this->head) {
            this->delete_head();
            return true;
        }
        else if (current==this->tail) {
            this->delete_last();
            return true;
        }
        else
        {
            current->next->prev=current->prev;
            current->prev->next=current->next;
            delete(current);
            return true;
        }
    }
    return false;
}

Iterator DLL::iterator() {
    Iterator it(*this);
    return it;
}

Iterator::Iterator(DLL &list) {
    this->list=list;
    this->current=this->list.head;
}

void Iterator::first() {
    this->current=this->list.head;
}

TElem Iterator::get_current() {
    if (this->current == NULL) {
        throw std::runtime_error("Get_Current!");
    }
    else
        return this->current->info;
}

bool Iterator::valid() {
    if (this->current==NULL)
        return false;
    else
        return true;
}

void Iterator::next() {
    if (this->current==NULL) {
        throw std::runtime_error("Next!");
    }
    else
        this->current = this->current->next;
}

/*
 * previous(iterator)
 *      if iterator->current == NIL
 *          throw "Prev!"
 *      else
 *          iterator->current = iterator->current->prev
 *      end_if
 */

void Iterator::previous()
//Time complexity: Theta(1)
{
    if(this->current==NULL)
        throw std::runtime_error("Prev!");
    else
        this->current = this->current->prev;
}

Iterator::Iterator() {
    this->current=NULL;
}