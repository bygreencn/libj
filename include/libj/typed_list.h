// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_LIST_H_
#define LIBJ_TYPED_LIST_H_

#include <libj/typed_iterator.h>

namespace libj {

template<typename L, typename T>
class TypedList : public L {
 public:
    virtual Boolean addTyped(const T& t) = 0;

    virtual Boolean addTyped(Size i, const T& t) = 0;

    virtual Boolean setTyped(Size i, const T& t) = 0;

    virtual T getTyped(Size i) const = 0;

    virtual T removeTyped(Size i) = 0;

    virtual Boolean removeTyped(const T& t) = 0;

    virtual typename TypedIterator<T>::Ptr iteratorTyped() const = 0;

    virtual typename TypedIterator<T>::Ptr reverseIteratorTyped() const = 0;

 public:
    virtual T shiftTyped() = 0;

    virtual Size unshiftTyped(const T& t) = 0;

    virtual Size pushTyped(const T& t) = 0;

    virtual T popTyped() = 0;
};

}  // namespace libj

#define LIBJ_TYPED_LIST(L, T) \
    public detail::Generic##L<TypedList<L, T>, T> { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(Typed##L, L)

#endif  // LIBJ_TYPED_LIST_H_
