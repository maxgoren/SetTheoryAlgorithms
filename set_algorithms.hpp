#ifndef set_algorithms_hpp
#define set_algorithms_hpp
#include <functional>
using std::less;

template <class T, typename comp = less<T>>
class SetMerger {
    private:
        virtual void predicateA(Set<T>& result) = 0;
        virtual void predicateB(Set<T>& result) = 0;
        virtual void predicateC(Set<T>& result) = 0;
        bool leftHasMore() {
            return lit != set_a.end();
        }
        bool rightHasMore() {
            return rit != set_b.end();
        }
        void init(Set<T>& a, Set<T>& b) {
            set_a = a; set_b = b;
            lit = set_a.begin(); rit = set_b.begin();
        }
    protected:
        SetMerger() { }
        T takeFromLeft() {
            return *lit++;
        }
        T takeFromRight() {
            return *rit++;
        }
        void merge(Set<T>& lhs, Set<T>& rhs, Set<T>& result) {
            init(lhs, rhs);
            while (leftHasMore() && rightHasMore()) {
                if (comp()(*lit , *rit)) {
                    predicateA(result);
                } else if (comp()(*rit, *lit)) {
                    predicateB(result);
                } else {
                    predicateC(result);
                }
            }
            while (leftHasMore()) result.insert(takeFromLeft());
            while (rightHasMore()) result.insert(takeFromRight()); 
        }
        typename Set<T>::iterator lit;
        typename Set<T>::iterator rit;
        Set<T> set_a;
        Set<T> set_b;
};

template <class T>
class Intersection : public SetMerger<T> {
    private:
        void predicateA(Set<T>& result) {
            this->takeFromLeft();
        }
        void predicateB(Set<T>& result) {
            this->takeFromRight();
        }
        void predicateC(Set<T>& result) {
            result.insert(this->takeFromLeft());
            this->takeFromRight();
        }
    public:
        Intersection(Set<T>& lhs, Set<T>& rhs, Set<T>& result) {
            this->merge(lhs, rhs, result);
        }
};

template <class T>
class Difference : public SetMerger<T> {
    private:
        void predicateA(Set<T>& result) {
            result.insert(this->takeFromLeft());
        }
        void predicateB(Set<T>& result) {
            this->takeFromRight();
        }
        void predicateC(Set<T>& result) {
            this->takeFromLeft();
            this->takeFromRight();
        }
    public:
        Difference(Set<T>& lhs, Set<T>& rhs, Set<T>& result) {
            this->merge(lhs, rhs, result);
        }
};

template <class T>
class SymmetricDifference : public SetMerger<T> {
    private:
        void predicateA(Set<T>& result) {
            result.insert(this->takeFromLeft());
        }
        void predicateB(Set<T>& result) {
            result.insert(this->takeFromRight());
        }
        void predicateC(Set<T>& result) {
            this->takeFromLeft();
            this->takeFromRight();
        }
        public:
            SymmetricDifference(Set<T>& lhs, Set<T>& rhs, Set<T>& result) {
                this->merge(lhs, rhs, result);
            }
};

template <class T>
class Union : public SetMerger<T> {
    private:
        void predicateA(Set<T>& result) {
            result.insert(this->takeFromRight());
        }
        void predicateB(Set<T>& result) {
            result.insert(this->takeFromLeft());
        }
        void predicateC(Set<T>& result) {
            result.insert(this->takeFromLeft());
            this->takeFromRight();
        }
    public:
        Union(Set<T>& lhs, Set<T>& rhs, Set<T>& result) {
            this->merge(lhs, rhs, result);
        }
};

#endif