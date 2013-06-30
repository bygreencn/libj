// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_XML_NODE_H_
#define LIBJ_XML_NODE_H_

#include <libj/mutable.h>
#include <libj/string.h>

namespace libj {
namespace xml {

class Document;
class NodeList;
class NamedNodeMap;

class Node : LIBJ_MUTABLE(Node)
 public:
    enum NodeType {
        ELEMENT_NODE                = 1,
        ATTRIBUTE_NODE              = 2,
        TEXT_NODE                   = 3,
        CDATA_SECTION_NODE          = 4,
        ENTITY_REFERENCE_NODE       = 5,
        ENTITY_NODE                 = 6,
        PROCESSING_INSTRUCTION_NODE = 7,
        COMMENT_NODE                = 8,
        DOCUMENT_NODE               = 9,
        DOCUMENT_TYPE_NODE          = 10,
        DOCUMENT_FRAGMENT_NODE      = 11,
        NOTATION_NODE               = 12,
    };

    virtual String::CPtr nodeName() const = 0;

    virtual String::CPtr nodeValue() const = 0;

    virtual void setNodeValue(String::CPtr val) = 0;

    virtual NodeType nodeType() const = 0;

    virtual Ptr parentNode() const = 0;

    virtual LIBJ_PTR(NodeList) childNodes() const = 0;

    virtual Ptr firstChild() const = 0;

    virtual Ptr lastChild() const = 0;

    virtual Ptr previousSibling() const = 0;

    virtual Ptr nextSibling() const = 0;

    virtual LIBJ_PTR(NamedNodeMap) attributes() const = 0;

    virtual LIBJ_CPTR(Document) ownerDocument() const = 0;

    virtual Boolean hasChildNodes() const = 0;

    virtual Boolean hasAttributes() const = 0;
};

}  // namespace xml
}  // namespace libj

#define LIBJ_XML_NODE(T) public libj::xml::Node { \
    LIBJ_MUTABLE_DEFS(T, libj::xml::Node)

#endif  // LIBJ_XML_NODE_H_
