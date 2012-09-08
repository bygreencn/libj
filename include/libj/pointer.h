// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_POINTER_H_
#define LIBJ_POINTER_H_

#include "libj/config.h"

namespace libj {

struct NullDeleter {
    void operator()(const void*) const {}
};

}  // namespace libj

#define LIBJ_NULL(T) static_cast<T*>(0)
#define LIBJ_NULL_DELETER libj::NullDeleter()

#ifdef LIBJ_USE_SP
    #include "libj/shared_ptr.h"
    #define LIBJ_PTR(T) libj::SharedPtr<T>::Type
    #define LIBJ_CPTR(T) libj::SharedPtr<const T>::Type
    #define LIBJ_PTR_TYPE(T) typename LIBJ_PTR(T)
    #define LIBJ_CPTR_TYPE(T) typename LIBJ_CPTR(T)
    #define LIBJ_STATIC_PTR_CAST(T) boost::static_pointer_cast<T>
    #define LIBJ_STATIC_CPTR_CAST(T) boost::static_pointer_cast<const T>
    #define LIBJ_NULL_PTR_DEF(T, V) \
        LIBJ_PTR(T) V(LIBJ_NULL(T), LIBJ_NULL_DELETER);
    #define LIBJ_NULL_CPTR_DEF(T, V) \
        LIBJ_CPTR(T) V(LIBJ_NULL(T), LIBJ_NULL_DELETER);
    #define LIBJ_NULL_PTR_TYPE_DEF(T, V) \
        typename LIBJ_NULL_PTR_DEF(T, V)
    #define LIBJ_NULL_CPTR_TYPE_DEF(T, V) \
        typename LIBJ_NULL_CPTR_DEF(T, V)
    #define LIBJ_SINGLETON_PTR_TYPE_DEF(T, V, I) \
        LIBJ_PTR_TYPE(T) V(I, LIBJ_NULL_DELETER);
#else
    #define LIBJ_PTR(T) T*
    #define LIBJ_CPTR(T) const T*
    #define LIBJ_PTR_TYPE(T) T*
    #define LIBJ_CPTR_TYPE(T) const T*
    #define LIBJ_STATIC_PTR_CAST(T) static_cast<T*>
    #define LIBJ_STATIC_CPTR_CAST(T) static_cast<const T*>
    #define LIBJ_NULL_PTR_DEF(T, V) \
        LIBJ_PTR(T) V(LIBJ_NULL(T));
    #define LIBJ_NULL_CPTR_DEF(T, V) \
        LIBJ_CPTR(T) V(LIBJ_NULL(T));
    #define LIBJ_NULL_PTR_TYPE_DEF(T, V) \
        LIBJ_NULL_PTR_DEF(T, V)
    #define LIBJ_NULL_CPTR_TYPE_DEF(T, V) \
        LIBJ_NULL_CPTR_DEF(T, V)
    #define LIBJ_SINGLETON_PTR_TYPE_DEF(T, V, I) \
        LIBJ_PTR_TYPE(T) V(I);
#endif

#endif  // LIBJ_POINTER_H_
