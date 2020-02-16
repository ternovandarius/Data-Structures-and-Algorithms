#pragma once

typedef int TElem;

class DNode:
private:
    TElem info;
    *TElem prev;
    *TElem next;
public:
    DNode(info);
