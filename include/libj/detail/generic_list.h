// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GENERIC_LIST_H_
#define LIBJ_DETAIL_GENERIC_LIST_H_

#include "./generic_collection.h"

namespace libj {
namespace detail {

template<typename T, typename B>
class GenericList : public GenericCollection<T, B> {
 public:
    virtual Size size() const = 0;

    virtual Boolean add(const Value& v) = 0;

    virtual Boolean addTyped(const T& t) = 0;

    virtual Boolean add(Size i, const Value& v) = 0;

    virtual Boolean addTyped(Size i, const T& t) = 0;

    virtual Boolean set(Size i, const Value& v) = 0;

    virtual Boolean setTyped(Size i, const T& t) = 0;

    virtual Value get(Size i) const = 0;

    virtual T getTyped(Size i) const = 0;

    virtual void clear() = 0;

    virtual Value remove(Size i) = 0;

    virtual T removeTyped(Size i) = 0;

    virtual Boolean remove(const Value& v) = 0;

    virtual Boolean removeTyped(const T& t) = 0;

    virtual Value subList(Size from, Size to) const = 0;

    virtual Iterator::Ptr iterator() const = 0;

    virtual Iterator::Ptr reverseIterator() const = 0;

    virtual typename TypedIterator<T>::Ptr iteratorTyped() const = 0;

    virtual typename TypedIterator<T>::Ptr reverseIteratorTyped() const = 0;

 public:
    virtual Size length() const {
        return size();
    }

    virtual Value shift() {
        return remove(static_cast<Size>(0));
    }

    virtual T shiftTyped() {
        return removeTyped(static_cast<Size>(0));
    }

    virtual Size unshift(const Value& val) {
        add(0, val);
        return size();
    }

    virtual Size unshiftTyped(const T& t) {
        addTyped(0, t);
        return size();
    }

    virtual Size push(const Value& val) {
        add(val);
        return size();
    }

    virtual Size pushTyped(const T& t) {
        addTyped(t);
        return size();
    }

    virtual Value pop() {
        Size len = size();
        if (len) {
            return remove(len - 1);
        } else {
            return UNDEFINED;
        }
    }

    virtual T popTyped() {
        Size len = size();
        if (len) {
            return removeTyped(len - 1);
        } else {
            LIBJ_THROW(Error::INDEX_OUT_OF_BOUNDS);
        }
    }

    virtual Int indexOf(const Value& val) {
        Size index = 0;
        Iterator::Ptr itr = iterator();
        while (itr->hasNext()) {
            if (itr->next().equals(val)) {
                return index;
            }
            index++;
        }
        return -1;
    }

    virtual Int lastIndexOf(const Value& val) {
        Size index = size() - 1;
        Iterator::Ptr itr = reverseIterator();
        while (itr->hasNext()) {
            if (itr->next().equals(val)) {
                return index;
            }
            index--;
        }
        return -1;
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_GENERIC_LIST_H_
