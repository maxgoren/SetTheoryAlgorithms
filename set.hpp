#ifndef set_hpp
#define set_hpp
#include <iostream>
#include "limits"
#include "listnode.hpp"
#include "list_iterator.hpp"
using namespace std;

template <class T>
class Set {
    public:
        using iterator = ForwardIterator<T>;
    private:
        using node = listnode<T>;
        using link = node*;
        link head;
        link z;
        int count;
        void init() {
            head = new node(std::numeric_limits<T>::min());
            z = new node(std::numeric_limits<T>::max());
            z->next = z;
            head->next = z;
            count = 0;
        }
    public:
        Set() {
            init();
        }
        Set(const Set& set) {
            init();
            link c = head;
            for (link it = set.head->next; it != set.z; it = it->next) {
                c->next = new node(it->info, z);
                c = c->next;
                count++;
            }
        }
        ~Set() {
            while (head != z) {
                link x = head;
                head = head->next;
                delete x;
            }
        }
        bool empty() {
            return head == z;
        }
        int size() {
            return count;
        }
        void insert(T key) {
            link t = new node(key);
            link x = head, p = x;
            while (x != z && key > x->info) {
                p = x;
                x = x->next;
            }
            if (key != x->info) {
                t->next = p->next;
                p->next = t;
                count++;
            }
        }
        iterator find(T key) {
            for (link it = head->next; it != z; it = it->next) {
                if (key == it->info) {
                    return iterator(it);
                }
            }
            return end();
        }
        iterator begin() {
            return iterator(head->next);
        }
        iterator end() {
            return iterator(z);
        }
        Set operator=(const Set& set) {
            if (this == &set)
                return *this;
            init();
            link c = head;
            for (link it = set.head->next; it != set.z; it = it->next) {
                c->next = new node(it->info, z);
                c = c->next;
                count++;
            }
            return *this;
        }
};

#endif