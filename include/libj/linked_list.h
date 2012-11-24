// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_LINKED_LIST_H_
#define LIBJ_LINKED_LIST_H_

#include "libj/list.h"

namespace libj {

class LinkedList : LIBJ_LIST(LinkedList)
 public:
    static Ptr create();
};

#define LIBJ_LINKED_LIST(T) public libj::LinkedList { \
    LIBJ_MUTABLE_DEFS(T, libj::LinkedList)

#define LIBJ_LINKED_LIST_TEMPLATE_DEFS(T) \
    LIBJ_MUTABLE_TEMPLATE_DEFS(T, libj::LinkedList)

}  // namespace libj

#endif  // LIBJ_LINKED_LIST_H_
