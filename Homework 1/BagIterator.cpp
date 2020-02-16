//
// Created by terno on 3/24/2019.
//

#include "BagIterator.h"

BagIterator::BagIterator(const Bag &c): con(c)
{
    this->current_position=0;
    this->freq_position=0;
}

void BagIterator::first() {
    this->current_position=0;
}

TElem BagIterator::getCurrent() const {
    return this->con.get_element(this->current_position);
}

bool BagIterator::valid() const {
    if (this->current_position==this->con->bagSize && this->freq_position==this->con->frequency[this->current_position])
        return false;
    return true;
}

void BagIterator::next() {
    if (this->valid())
    {
        if (this->freq_position==this->con->frequency[this->current_position])
        {
            this->current_position++;
            this->freq_position=0;
        }
    }
    else
        throw("Invalid!");
}