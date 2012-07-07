// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/js_regexp.h"
#include "libj/undefined.h"
#include "./glue/regexp.h"

namespace libj {

class JsRegExpImpl : public JsRegExp {
 public:
    static Ptr create(String::CPtr pattern, UInt flags) {
        Ptr p(new JsRegExpImpl(pattern, flags));
        return p;
    }

    Boolean global() const {
        return flags_ & GLOBAL;
    }

    Boolean ignoreCase() const {
        return flags_ & IGNORE_CASE;
    }

    Boolean multiline() const {
        return flags_ & MULTILINE;
    }

    String::CPtr source() const {
        return pattern_;
    }

    JsArray::Ptr exec(String::CPtr str) const {
        if (!str) {
            LIBJ_NULL_PTR(JsArray, nullp);
            return nullp;
        }

        std::vector<int> captures;
        re_->execute(str->toStdU16String(), 0, captures);
        if (captures.empty()) {
            LIBJ_NULL_PTR(JsArray, nullp);
            return nullp;
        }

        JsArray::Ptr res = JsArray::create();
        Size len = captures.size();
        for (Size i = 0; i < len; i += 2) {
            if (captures[i] >= 0 &&
                captures[i+1] >= 0 &&
                captures[i] < captures[i+1] &&
                captures[i+1] <= static_cast<int>(str->length())) {
                res->add(str->substring(captures[i], captures[i+1]));
            } else {
                res->add(Undefined::instance());
            }
        }
        return res;
    }

    Boolean test(String::CPtr str) const {
        return !!exec(str);
    }

 private:
    JsObject::Ptr obj_;
    String::CPtr pattern_;
    UInt flags_;
    glue::RegExp* re_;

    JsRegExpImpl(String::CPtr pattern, UInt flags)
        : obj_(JsObject::create())
        , pattern_(pattern)
        , flags_(flags)
        , re_(glue::RegExp::create(pattern->toStdU16String(), flags)) {}
 public:
    ~JsRegExpImpl() {
        delete re_;
    }

    LIBJ_JS_OBJECT_IMPL(obj_);
};

JsRegExp::Ptr JsRegExp::create(String::CPtr pattern, UInt flags) {
    return JsRegExpImpl::create(pattern, flags);
}

}  // namespace libj
