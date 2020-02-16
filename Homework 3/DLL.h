#pragma once

typedef int TElem;

class DNode{
private:

public:
    TElem info;
    DNode *prev;
    DNode *next;
    DNode(TElem info);
    DNode();
};

class Iterator;

class DLL {
    friend class Iterator;
private:

public:
    DNode *head = NULL;
    DNode *tail = NULL;
    TElem search_by_val(int val) const;

    TElem search_by_pos(int pos);

    void add_head(TElem elem);

    bool add_mid(TElem elem, int pos);

    void add_tail(TElem elem);

    void delete_head();

    bool delete_elem(TElem elem);

    void delete_last();

    Iterator iterator();
};

class Iterator{
    friend class DLL;
private:
    DLL list;
    DNode *current;

public:
    Iterator();
    Iterator(DLL &list);
    void first();
    TElem get_current();
    bool valid();
    void next();
    void previous();
};