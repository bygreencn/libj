// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_ARRAY_LIST_H_
#define LIBJ_TYPED_ARRAY_LIST_H_

#include "libj/array_list.h"
#include "libj/error.h"
#include "libj/exception.h"
#include "libj/string.h"
#include "libj/typed_iterator.h"

namespace libj {

template<typename T>
class TypedArrayList : LIBJ_ARRAY_LIST_TEMPLATE(TypedArrayList<T>)
 protected:
    Boolean match(const Value& v) {
        TypeId id = Type<T>::id();
        Boolean result = v.type() == id || v.instanceof(id);
#ifdef LIBJ_USE_EXCEPTION
        if (!result)
            LIBJ_THROW(Error::ILLEGAL_TYPE);
#endif  // LIBJ_USE_EXCEPTION
        return result;
    }

 public:
    Size size() const {
        return list_->size();
    }

    Boolean add(const Value& v) {
        if (match(v)) {
            return list_->add(v);
        } else {
            return false;
        }
    }

    Boolean add(Size i, const Value& v) {
        if (match(v)) {
            return list_->add(i, v);
        } else {
            return false;
        }
    }

    Boolean set(Size i, const Value& v) {
        if (match(v)) {
            return list_->set(i, v);
        } else {
            return false;
        }
    }

    Value get(Size i) const {
        return list_->get(i);
    }

    Value remove(Size i) {
        return list_->remove(i);
    }

    Boolean remove(const Value& v) {
        return list_->remove(v);
    }

    void clear() {
        return list_->clear();
    }

    String::CPtr toString() const {
        return list_->toString();
    }

    Iterator::Ptr iterator() const {
        return list_->iterator();
    }

#ifdef LIBJ_USE_EXCEPTION
    T getTyped(Size i) const {
        if (i >= size()) {
            LIBJ_THROW(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            Value v = list_->get(i);
            T t;
            if (to<T>(v, &t))
                return t;
            else
                LIBJ_THROW(Error::ILLEGAL_STATE);
        }
    }

    typename TypedIterator<T>::Ptr iteratorTyped() const {
        return TypedIterator<T>::create(iterator());
    }
#endif  // LIBJ_USE_EXCEPTION

 public:
    static Ptr create() {
        Ptr p(new TypedArrayList());
        return p;
    }

    static Ptr create(ArrayList::CPtr a) {
        Ptr p(new TypedArrayList());
        Iterator::Ptr itr = a->iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            if (p->match(v)) {
                p->add(v);
            } else {
                return null();
            }
        }
        return p;
    }

 protected:
    TypedArrayList() : list_(ArrayList::create()) {}

    ArrayList::Ptr list_;
};

#define LIBJ_TYPED_ARRAY_LIST_TEMPLATE(D, T) public libj::TypedArrayList<T> { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(D<T>, libj::TypedArrayList<T>)

}  // namespace libj

#endif  // LIBJ_TYPED_ARRAY_LIST_H_
