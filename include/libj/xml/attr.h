// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_XML_ATTR_H_
#define LIBJ_XML_ATTR_H_

#include <libj/xml/node.h>

namespace libj {
namespace xml {

class Element;

class Attr : LIBJ_XML_NODE(Attr)
 public:
    virtual String::CPtr name() const = 0;

    virtual String::CPtr value() const = 0;

    virtual LIBJ_CPTR(Element) ownerElement() const = 0;
};

}  // namespace xml
}  // namespace libj

#endif  // LIBJ_XML_ATTR_H_
