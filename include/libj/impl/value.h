// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_VALUE_H_
#define LIBJ_IMPL_VALUE_H_

namespace libj {

template<typename T>
inline Boolean to(const Value & val, T* out) {
    return detail::to<T>(val, out);
}

template<typename T>
inline typename Type<T>::Ptr toPtr(const Value& v) {
    LIBJ_PTR_TYPE(T) p;
    if (v.instanceof(Type<T>::id()) &&
        !v.isCPtr() &&
        to<typename Type<T>::Ptr>(v, &p, true)) {
        return p;
    } else {
        LIBJ_NULL_PTR_TYPE_DEF(T, nullp);
        return nullp;
    }
}

template<typename T>
inline typename Type<T>::CPtr toCPtr(const Value& v) {
    LIBJ_CPTR_TYPE(T) p;
    if (v.instanceof(Type<T>::id()) &&
        to<typename Type<T>::CPtr>(v, &p, true)) {
        return p;
    } else {
        LIBJ_NULL_CPTR_TYPE_DEF(T, nullp);
        return nullp;
    }
}

}  // namespace libj

#endif  // LIBJ_IMPL_VALUE_H_
