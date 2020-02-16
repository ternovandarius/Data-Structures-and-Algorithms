//
// Created by terno on 4/14/2019.
//

#include "DLLA.h"
#include <exception>

DNode::DNode(TKey info) {
    this->info=info;
    next=-1;
    prev=-1;
}

DNode::DNode() {
    this->info=0;
    this->next=-1;
    this->prev=-1;
}

DLLA::DLLA() {
    this->cap=10;
    DNode *array=new DNode[10];
    this->nodes=array;
    this->head=-1;
    this->tail=-1;
    this->firstEmpty=0;
}

int DLLA::allocate() {
    TKey newElem=this->firstEmpty;
    if (newElem!=-1)
    {
        this->firstEmpty=this->nodes[this->firstEmpty].next;
        if(this->firstEmpty!=-1)
            this->nodes[this->firstEmpty].prev=-1;
        this->nodes[newElem].next=-1;
        this->nodes[newElem].prev=-1;
    }
    return newElem;
}

void DLLA::free(int pos) {
    this->nodes[pos].next=this->firstEmpty;
    this->nodes[pos].prev=-1;
    if (this->firstEmpty!=-1)
        this->nodes[this->firstEmpty].prev=pos;
    this->firstEmpty=pos;
}

void DLLA::add_head(TElem e) {
    DNode node(e.first);
    if(this->head==-1)
    {
        this->nodes[0]=node;
        this->nodes[0].values.add(e.second);
        this->head=0;
        this->tail=0;
        this->firstEmpty=1;
    }
    else
    {
        this->nodes[this->firstEmpty]=node;
        this->nodes[this->firstEmpty].values.add(e.second);
        this->nodes[this->firstEmpty].prev=-1;
        this->nodes[this->firstEmpty].next=this->head;
        this->head=this->firstEmpty;
        this->nodes[this->nodes[this->head].next].prev=this->head;
        this->firstEmpty++;
    }
}

void DLLA::add_tail(TElem e) {
    DNode node(e.first);
    if(this->tail==-1)
    {
        this->nodes[0]=node;
        this->nodes[0].values.add(e.second);
        this->head=0;
        this->tail=0;
        this->firstEmpty=1;
    }
    else
    {
        this->nodes[this->firstEmpty]=node;
        this->nodes[this->firstEmpty].values.add(e.second);
        this->nodes[this->firstEmpty].prev=this->tail;
        this->nodes[this->firstEmpty].next=-1;
        this->tail=this->firstEmpty;
        this->nodes[this->nodes[this->tail].prev].next=this->tail;
        this->firstEmpty++;
    }
}

bool DLLA::add_mid(TElem e) {
    if(this->cap-1<=this->firstEmpty)
    {
        DNode * newNodes = new DNode[2*this->cap];
        for(int i=0; i<this->cap; i++)
            newNodes[i]=this->nodes[i];
        delete[] this->nodes;
        this->nodes=newNodes;
        this->cap*=2;
    }
    if (this->head==-1)
    {
        this->add_head(e);
        return true;
    }
    else if (this->tail==-1)
    {
        this->add_tail(e);
        return true;
    }
    else{
        DNode *current;
        current=&this->nodes[this->head];
        int current_pos=this->head;
        while(current->info!=e.first and current->next!=-1) {
            current_pos = current->next;
            current = &this->nodes[current->next];
        }
        if(current->info==e.first)
            this->nodes[current_pos].values.add(e.second);
        else
        {
            DNode newNode(e.first);
            this->nodes[this->firstEmpty]=newNode;
            this->nodes[this->firstEmpty].values.add(e.second);
            this->nodes[current_pos].next=this->firstEmpty;
            //this->nodes[this->firstEmpty].prev=this->nodes[this->nodes[current_pos].prev].next;
            this->firstEmpty++;
        }
    }
}

int DLLA::get_size(){
    int size=0;
    if(!this->isEmpty()) {
        DNode d = this->nodes[this->head];
        while(d.next!=-1)
        {
            MiniNode v=d.values[d.values.head];
            while(v.next!=-1)
            {
                size++;
                v=d.values[v.next];
            }
            size++;
            d=this->nodes[d.next];
        }
        MiniNode v=d.values[d.values.head];
        while(v.next!=-1)
        {
            size++;
            v=d.values[v.next];
        }
        size++;
    }
    return size;
}

bool DLLA::isEmpty() {
    if (this->firstEmpty==0)
        return true;
    return false;
}

bool DLLA::search_by_pos(int pos)
{
    int current=this->head;
    while(current!=pos or current!=-1)
        current=this->nodes[current].next;
    if(current==pos)
    {
        return true;
    }
    else
        return false;
}

DNode DLLA::operator[](int pos) {
    if(pos<this->get_size())
        return this->nodes[pos];
}

void MiniNode::set_next(int n) {
    this->next=n;
}

void MiniNode::set_prev(int p) {
    this->prev=p;
}

bool DLLA::remove(TElem e) {
    DNode * current=&this->nodes[this->head];
    int current_pos=this->head;
    while(current->info!=e.first and current->next!=-1)
    {
        current_pos=current->next;
        current=&this->nodes[current->next];
    }
    if(current->info==e.first)
    {
        MiniNode c=current->values[current->values.head];
        int cpos=current->values.head;
        while(c.next!=-1 and c.info!=e.second) {
            cpos = c.next;
            c = current->values[c.next];
        }
        if(c.info==e.second)
        {
            current->values.firstEmpty=cpos;
            if(c.next!=-1 and c.prev!=-1)
            {
                current->values[c.prev].set_next(c.next);
                current->values[c.next].set_prev(c.prev);
            }
            else if(c.next==-1)
            {
                current->values[c.prev].set_next(-1);
                current->values.tail=c.prev;
            }
            else if(c.prev==-1)
            {
                current->values.head=c.next;
                current->values[c.next].set_prev(-1);
            }
            else
            {
                this->firstEmpty=current_pos;
                if(current->next!=-1 and current->prev!=-1) {
                    this->nodes[current->prev].next = current->next;
                    this->nodes[current->next].prev = current->prev;
                }
                else if(current->next==-1)
                {
                    this->nodes[current->prev].next=-1;
                    this->tail=current->prev;
                }
                else if(current->prev==-1)
                {
                    this->nodes[current->next].prev=-1;
                    this->head=current->next;
                }
                else
                {
                    delete[] this->nodes;
                    this->nodes=new DNode[10];
                    this->cap=10;
                    this->head=-1;
                    this->tail=-1;
                    this->firstEmpty=0;
                }
            }
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

std::vector<TValue> DLLA::search(TKey c) {
    std::vector<TValue> vec;
    DNode * current=&this->nodes[this->head];
    while(current->next!=-1 and current->info!=c)
    {
        current=&this->nodes[current->next];
    }
    if(current->info==c)
    {
        MiniNode n=current->values[current->values.head];
        while(n.next!=-1)
        {
            vec.push_back(n.info);
            n=current->values[n.next];
        }
        vec.push_back(n.info);
    }
    return vec;
}

MiniNode MiniDLLA::operator[](int pos) {
    return this->elems[pos];
}

DLLAIterator::DLLAIterator(DLLA &list){
    this->d=list;
}

void DLLAIterator::first() {
    this->c=this->d.head;
}

bool DLLAIterator::valid() {
    if(this->c>=this->d.get_size())
        return false;
    else
        return true;
}

DNode DLLAIterator::getCurrent() {
    return this->d[this->c];
}

void DLLAIterator::next() {
    if(this->d[this->c].next==-1)
        throw std::runtime_error("Bad next!");
    else
        this->c=this->d[this->c].next;
}

DLLAIterator DLLA::iterator(){
    DLLAIterator i(*this);
    return i;
}

DLLAIterator::DLLAIterator() {
    DLLA d;
    this->d=d;
}

void testDLLA(){
    DLLA d;
    TElem e1(2, 2);
    d.add_mid(e1);
    TElem e2(3, 3);
    d.add_mid(e2);
    TElem e3(4, 4);
    TElem e4(3, 15);
    TElem e5(2, 14);
    d.add_mid(e3);
    d.add_mid(e4);
    d.add_mid(e5);
    DLLAIterator i=d.iterator();
    i.first();
    std::cout<<i.getCurrent().info;
    i.next();
    std::cout<<i.getCurrent().info;
    i.next();
    std::cout<<i.getCurrent().info;
    try{
        i.next();
    }
    catch(std::exception e){
        std::cout<<"a";
    }
}

MiniDLLA::MiniDLLA() {
    this->cap=10;
    this->elems=new MiniNode[10];
    this->head=-1;
    this->tail=-1;
    this->firstEmpty=0;
}

MiniNode::MiniNode(TKey info) {
    this->info=info;
    this->next=-1;
    this->prev=-1;
}

MiniNode::MiniNode() {
    this->info=0;
    this->next=-1;
    this->prev=-1;
}

void MiniDLLA::add(TValue e) {
    if(this->cap-1<=this->firstEmpty)
    {
        MiniNode * newNodes = new MiniNode[2*this->cap];
        for(int i=0; i<this->cap; i++)
            newNodes[i]=this->elems[i];
        delete[] this->elems;
        this->elems=newNodes;
        this->cap*=2;
    }
    MiniNode m(e);
    this->elems[this->firstEmpty] = m;
    if (this->head == -1) {
        this->head = this->firstEmpty;
        this->tail = this->firstEmpty;
        this->firstEmpty++;
    }
    else{
        this->elems[this->firstEmpty-1].next=this->firstEmpty;
        this->elems[this->firstEmpty]=m;
        this->elems[this->firstEmpty].prev=this->firstEmpty-1;
        this->firstEmpty++;
    }
}