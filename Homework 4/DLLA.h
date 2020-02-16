#pragma once
#include <vector>

typedef int TKey;

typedef int TValue;


typedef std::pair<TKey, TValue> TElem;

class DLLA;
class DLLAIterator;
class DNode;

class MiniNode{
public:
    TKey info;
    int next;
    int prev;
    MiniNode(TKey info);
    MiniNode();
    void set_next(int n);
    void set_prev(int p);
};

class MiniDLLA{
    friend class DNode;
private:

public:
    MiniNode * elems=new MiniNode[10];
    int cap;
    int head;
    int tail;
    int firstEmpty;
    MiniNode operator[](int pos);
    MiniDLLA();
    void add(TValue e);
};

class DNode{
    friend class DLLA;
    friend class MiniDLLA;
public:
    MiniDLLA values;
    TKey info;
    int next;
    int prev;
    DNode(TKey info);
    DNode();
};

class DLLA{
    friend class DNode;
    friend class DLLAIterator;
private:

    int cap;
    int head;
    int tail;



public:
    int firstEmpty;
    DNode *nodes=new DNode[10];
    DLLA();
    int allocate();
    void free(int pos);
    void add_head(TElem e);
    void add_tail(TElem e);
    bool add_mid(TElem e);
    int get_size();
    bool isEmpty();
    bool search_by_pos(int pos);
    DNode operator[](int pos);
    DLLAIterator iterator();
    bool remove(TElem e);
    std::vector<TValue> search(TKey c);
};

class DLLAIterator{
private:
    DLLA d;
    int c=0;
public:
    DLLAIterator();
    DLLAIterator(DLLA &list);
    void first();
    DNode getCurrent();
    bool valid();
    void next();
};