#ifndef listnode_hpp
#define listnode_hpp

template <typename T>
struct listnode {
    T info;
    listnode* next;
    listnode(T i = T(), listnode* n = nullptr)  {
        info = i;
        next = n;
    }
};

template <typename T>
struct dlistnode {
    T info;
    dlistnode* next;
    dlistnode* prev;
    dlistnode(T i, dlistnode* p, dlistnode* n) {
        info = i;
        next = n;
        prev = p;
    }
    dlistnode(T i) {
        info = i;
        next = nullptr; 
        prev = nullptr;
    }
    dlistnode() {
        next = nullptr;
        prev = nullptr;
    }
};

#endif