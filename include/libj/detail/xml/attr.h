// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_XML_ATTR_H_
#define LIBJ_DETAIL_XML_ATTR_H_

#include <libj/xml/attr.h>
#include <libj/detail/xml/node.h>

namespace libj {
namespace detail {
namespace xml {

class Attr : public Node<libj::xml::Attr> {
 public:
    Attr(
        libj::xml::Document::CPtr root,
        const pugi::xml_attribute& attr)
        : attr_(attr.internal_object()) {
        root_ = root;
        if (attr_) {
            name_ = createString(attr_.name());
            value_ = createString(attr_.value());
        } else {
            name_ = String::create();
            value_ = String::create();
        }
    }

    virtual String::CPtr name() const {
        return name_;
    }

    virtual String::CPtr value() const {
        return value_;
    }

 public:
    virtual String::CPtr nodeName() const {
        return name();
    }

    virtual String::CPtr nodeValue() const {
        return value();
    }

    virtual NodeType nodeType() const {
        return ATTRIBUTE_NODE;
    }

    virtual libj::xml::Node::CPtr parentNode() const {
        return libj::xml::Node::null();
    }

    virtual libj::xml::NodeList::CPtr childNodes() const {
        // TODO(plenluno): check
        return libj::xml::NodeList::null();
    }

    virtual libj::xml::Node::CPtr firstChild() const {
        // TODO(plenluno): check
        return libj::xml::Node::null();
    }

    virtual libj::xml::Node::CPtr lastChild() const {
        // TODO(plenluno): check
        return libj::xml::Node::null();
    }

    virtual libj::xml::Node::CPtr previousSibling() const {
        return libj::xml::Node::null();
    }

    virtual libj::xml::Node::CPtr nextSibling() const {
        return libj::xml::Node::null();
    }

    virtual libj::xml::NamedNodeMap::CPtr attributes() const {
        return libj::xml::NamedNodeMap::null();
    }

    virtual Boolean hasChildNodes() const {
        // TODO(plenluno): check
        return false;
    }

    virtual Boolean hasAttributes() const {
        return false;
    }

 private:
    pugi::xml_attribute attr_;
    String::CPtr name_;
    String::CPtr value_;
};

inline libj::xml::Attr::CPtr createAttr(
    libj::xml::Document::CPtr root,
    const pugi::xml_attribute& attr) {
    return libj::xml::Attr::CPtr(new Attr(root, attr));
}

}  // namespace xml
}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_XML_ATTR_H_
