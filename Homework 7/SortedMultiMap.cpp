#include "SortedMultiMap.h"

DNode::DNode() {
    this->values=new TValue[10];
    this->next=-1;
    this->prev=-1;
    this->realPrev=-1;
    this->info=0;
}

DNode::DNode(TKey info) {
    this->values=new TValue[10];
    this->next=-1;
    this->prev=-1;
    this->realPrev=-1;
    this->info=info;
    this->size=0;
}

void DNode::add(TValue v) {
    if(this->size==this->cap)
    {
        TValue newValues[this->cap*2];
        for(int i=0; i<this->cap; i++)
        {
            newValues[i]=this->values[i];
        }
        delete[] this->values;
        this->values=newValues;
    }
    this->values[this->size++]=v;
}

SortedMultiMap::SortedMultiMap(Relation r) {
    this->r=r;
    this->cap=10;
    this->firstEmpty=0;
    this->head=-1;
    this->tail=-1;
    this->realHead=0;
}

void SortedMultiMap::add(TKey c, TValue v) {
    if (this->head==-1)
    {
        DNode n(c);
        n.add(v);
        this->nodes[this->firstEmpty]=n;
        this->head=0;
        this->tail=0;
        this->firstEmpty=1;
        this->fakeSize=1;
        this->realHead=0;
    } else{
        DNode *current=&this->nodes[this->realHead];
        while(current->next!=-1 and current->info!=c)
            current=&this->nodes[current->next];
        if (current->info==c) {
            current->add(v);
            this->fakeSize++;
        }
        else{
            if(this->cap-1<=this->firstEmpty)
            {
                DNode * newNodes = new DNode[2*this->cap];
                for(int i=0; i<this->cap; i++)
                    newNodes[i]=this->nodes[i];
                delete[] this->nodes;
                this->nodes=newNodes;
                this->cap*=2;
            }
            DNode n(c);
            n.add(v);
            this->nodes[this->firstEmpty++]=n;
            DNode *current2=&this->nodes[this->realHead];
            DNode *prev;
            int pos=0;
            int ok=0;
            this->fakeSize++;
            while(ok==0)
            {
                if(current2->info<c)
                {
                    if(current2->next==-1)
                    {
                        this->tail=this->firstEmpty-1;
                        current2->next=this->firstEmpty-1;
                        ok=1;
                    }
                    else
                    {
                        pos=current2->next;
                        current2=&this->nodes[current2->next];
                    }
                }
                else{
                    if(current2->prev==-1)
                    {
                        this->realHead=this->firstEmpty-1;
                        current2->prev=this->firstEmpty-1;
                        ok=1;
                    }
                    else
                    {
                        pos=current2->prev;
                        current2=&this->nodes[current2->prev];
                    }
                }
            }
        }
    }
}

int SortedMultiMap::size() const {
    return this->fakeSize;
}

bool SortedMultiMap::isEmpty() const {
    return (this->fakeSize==0);
}

SortedMultiMap::~SortedMultiMap()=default;

vector<TValue> SortedMultiMap::search(TKey c) const {
    DNode *current=&this->nodes[this->realHead];
    vector<TValue> v;
    while(current->info!=c and current->next!=-1)
        current=&this->nodes[current->next];
    if(current->info==c)
        for(int i=0; i<current->size; i++)
            v.push_back(current->values[i]);
    return v;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    if (this->head==-1)
        return false;
    else
    {
        DNode *current=&this->nodes[this->realHead];
        while(current->info!=c and current->next!=-1)
            current=&this->nodes[current->next];
        if(current->info!=c)
            return false;
        else{
            if(current->size!=1) {
                for (int i = 0; i < current->size; i++)
                    if (current->values[i] == v and i != current->size - 1) {
                        for (int j = i; j < current->size - 1; j++)
                            current->values[j] = current->values[j + 1];
                        current->size--;
                        this->fakeSize--;
                        return true;
                    } else if (current->values[i] == v and i == current->size - 1) {
                        current->values[i] = NULL;
                        current->size--;
                        this->fakeSize--;
                        return true;
                    }
                return false;
            }
            else if (current->size==1)
            {
                if(current->values[this->head]!=v)
                    return false;
                else
                {
                    this->fakeSize--;
                    if (current->next==-1 and current->prev==-1) {
                        int to_remove;
                        for (int i = 0; i < cap; i++) {
                            if (this->nodes[i].prev == current->info) {
                                to_remove = this->nodes[i].prev;
                                this->nodes[i].prev = -1;
                            }
                            if (this->nodes[i].next == current->info) {
                                to_remove = this->nodes[i].next;
                                this->nodes[i].next = -1;
                            }
                        }
                        //this->nodes[to_remove] = NULL;
                        this->firstEmpty = to_remove;
                    }
                    else if(current->next==-1)
                    {
                        int to_remove;
                        for (int i = 0; i < cap; i++) {
                            if (this->nodes[i].prev == current->info) {
                                to_remove = this->nodes[i].prev;
                                this->nodes[i].prev = current->prev;
                            }
                            if (this->nodes[i].next == current->info) {
                                to_remove = this->nodes[i].next;
                                this->nodes[i].next = current->prev;
                            }
                        }
                        this->nodes[to_remove] = NULL;
                        this->firstEmpty = to_remove;
                    }
                    else if(current->prev==-1){
                        int to_remove;
                        for (int i = 0; i < cap; i++) {
                            if (this->nodes[i].prev == current->info) {
                                to_remove = this->nodes[i].prev;
                                this->nodes[i].prev = current->next;
                            }
                            if (this->nodes[i].next == current->info) {
                                to_remove = this->nodes[i].next;
                                this->nodes[i].next = current->next;
                            }
                        }
                        this->nodes[to_remove] = NULL;
                        this->firstEmpty = to_remove;
                    }
                    else{
                        DNode *current2=&this->nodes[current->next];
                        while(current2->prev!=-1)
                        {
                            current2=&this->nodes[current2->prev];
                        }
                        int to_remove;
                        for (int i = 0; i < cap; i++) {
                            if (this->nodes[i].prev == current2->info) {
                                to_remove = this->nodes[i].prev;
                                this->nodes[i].prev = current2->next;
                            }
                            if (this->nodes[i].next == current2->info) {
                                to_remove = this->nodes[i].next;
                                this->nodes[i].next = current2->next;
                            }
                        }
                        current->info=current2->info;
                        current->values=current2->values;
                        current->size=current2->size;
                        current->cap=current2->cap;
                        this->nodes[to_remove] = NULL;
                        this->firstEmpty = to_remove;
                    }
                    return true;
                }
            }
        }
    }
}

SMMIterator::SMMIterator(SortedMultiMap &s): s{s} {}

void SMMIterator::first() {
    this->c=this->s.realHead;
    this->ci=0;
}

void SMMIterator::next() {
    if(this->valid())
    {
        if(this->ci==this->s.nodes[c].size)
        {
            this->ci=0;
            this->c=this->s.nodes[c].next;
        }
        else{
            this->ci++;
        }
    }
}

bool SMMIterator::valid() {
    if(this->s.nodes[c].next==-1)
        return false;
    else
        return true;
}

TElem SMMIterator::getCurrent() {
    int y=this->s.nodes[c].values[ci];
    int x=this->s.nodes[c].info;
    TElem t(x, y);
    return t;
}

SMMIterator SortedMultiMap::iterator(){
    SMMIterator it(*this);
    return it;
}

ValueIterator::ValueIterator(SortedMultiMap s, TKey k): s{s}, k{k} {
    //theta(1)
    this->vec=s.search(k);
    if(vec.empty())
        this->c=-1;
    else{
        this->c=0;
    }
}

void ValueIterator::first() {
    //theta(1)
    if(this->c==-1)
        throw(std::runtime_error("Key has not been found!"));
    else
        this->c=0;
}

TValue ValueIterator::getCurrent() {
    //theta(1)
    if(!this->valid())
       throw(std::runtime_error("Invalid!"));
    else
        return this->vec[this->c];
}

bool ValueIterator::valid() {
    //theta(1)
    if(this->c==-1 or this->c>=this->vec.size())
        return false;
    return true;
}

void ValueIterator::next() {
    //theta(1)
    if(this->valid())
        if(this->c<this->vec.size()-1)
            this->c++;
        else
            throw(std::runtime_error("Invalid!"));
    else
        throw(std::runtime_error("Invalid!"));
}

/*
 * ValueIterator(s:SortedMultiMap, k:TKey)
 *      this->k<-k
 *      this->s<-s
 *      this->vec<-vec
 *      if this->vec.empty() then
 *          this->c<--1
 *      else
 *          this->c<-0
 *      end_if
 * end_ValueIterator
 *
 * getCurrent(v:ValueIterator)
 *      if v.valid!=true then
 *         throw exception
 *      else
 *         getCurrent<-v.vec[v.c]
 *      end_if
 * end_getCurrent
 *
 * first(v:ValueIterator)
 *      if v.c==-1 then
 *          throw exception
 *      else
 *          v.c=0
 *      end_if
 * end_first
 *
 * valid(v:ValueIterator)
 *      if v.c==-1 || v.c>=v.vec.size() then
 *          valid<-false
 *      valid<-true
 * end_valid
 *
 * next(v:ValueIterator)
 *      if v.valid() then
 *          if v.c<v.vec.size()-1 then
 *              v.c=v.c+1
 *          else
 *              throw exception
 *          end_if
 *      else
 *          throw exception
 *      end_if
 * end_next
 */