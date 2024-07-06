#ifndef list_iterator_hpp
#define list_iterator_hpp

template <typename T>
class ForwardIterator {
    private:
        listnode<T>* curr;
    public:
        ForwardIterator(listnode<T>* pos) {
            curr = pos;
        }
        ForwardIterator() {
            curr = nullptr;
        }
        T& operator*() {
            return curr->info;
        }
        ForwardIterator operator++() {
            curr = curr->next;
            return *this;
        }
        ForwardIterator operator++(int) {
            ForwardIterator t = *this;
            ++*this;
            return t;
        }
        bool operator==(const ForwardIterator& it) const {
            return curr == it.curr;
        }
        bool operator!=(const ForwardIterator& it) const {
            return !(*this == it);
        }
};

template <typename T>
class BiDirectionalIterator {
    private:
        using node = dlistnode<T>;
        using link = node*;
        link curr;
    public:
        BiDirectionalIterator(link pos) {
            curr = pos;
        }
        T& operator*() {
            return curr->info;
        }
        BiDirectionalIterator operator++() {
            curr = curr->next;
            return *this;
        }
        BiDirectionalIterator operator++(int) {
            BiDirectionalIterator t = *this;
            ++*this;
            return t;
        }
        BiDirectionalIterator operator--() {
            curr = curr->prev;
            return *this;
        }
        BiDirectionalIterator operator--(int) {
            BiDirectionalIterator t = *this;
            --*this;
            return t;
        }
        bool operator==(const BiDirectionalIterator& it) const {
            return curr == it.curr;
        }
        bool operator!=(const BiDirectionalIterator& it) const {
            return !(*this == it);
        }
};

#endif