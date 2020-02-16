#include "MultiMap.h"

MultiMap::MultiMap(){
    this->d=new DLLA;
}

MultiMap::~MultiMap()=default;

void MultiMap::add(TKey c, TValue v) {
    TElem e(c, v);
    this->d->add_mid(e);
}

int MultiMap::size(){
    return this->d->get_size();
}

bool MultiMap::isEmpty() const {
    return this->d->isEmpty();
}

bool MultiMap::remove(TKey c, TValue v) {
    TElem e(c, v);
    return this->d->remove(e);
}

vector<TValue> MultiMap::search(TKey c) const {
    return this->d->search(c);
}

MultiMapIterator::MultiMapIterator(MultiMap &m) {
    this->m=m;
}

MultiMapIterator MultiMap::iterator() {
    MultiMapIterator it(*this);
    return it;
}

void MultiMapIterator::first() {
    this->c=0;
    this->ci=0;
}

TElem MultiMapIterator::getCurrent() {
    int key=m.d->nodes[c].info;
    int val= m.d->nodes[c].values[ci].info;
    TElem e(key, val);
    return e;
}

bool MultiMapIterator::valid() {
    if(this->m.d->nodes[c].next==-1)
        return false;
    else{
        if(this->m.d->nodes[c].values[ci].next==-1)
        {
            return false;
        }
        else
            return true;
    }
}

void MultiMapIterator::next() {
    if(this->valid())
    {
        if(this->ci==this->m.d->nodes[c].values.firstEmpty)
        {
            this->ci=0;
            this->c++;
        }
        else
            this->ci++;
    }
}