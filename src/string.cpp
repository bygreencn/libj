// Copyright (c) 2012 Plenluno All rights reserved.

#include <assert.h>
#include <stdio.h>
#include <iv/lv5/third_party/v8_dtoa/conversions.h>

#include "libj/string.h"
#include "./glue/cvtutf.h"

namespace libj {

class StringImpl : public String {
 public:
    Size length() const {
        return str_.length();
    }

    Char charAt(Size index) const {
        if (index >= length()) {
            return NO_CHAR;
        } else {
            return str_.at(index);
        }
    }

    CPtr substring(Size begin) const {
        if (begin > length()) {
            return null();
        } else if (begin == 0) {
            return toString();
        } else {
            CPtr p(new StringImpl(*this, begin));
            return p;
        }
    }

    CPtr substring(Size begin, Size end) const {
        Size len = length();
        if (begin > len || end > len || begin > end) {
            return null();
        } else if (begin == 0 && end == len) {
            return toString();
        } else {
            CPtr p(new StringImpl(*this, begin, end - begin));
            return p;
        }
    }

    CPtr concat(CPtr other) const {
        if (!other || other->isEmpty()) {
            return this->toString();
        } else if (this->isEmpty()) {
            return other->toString();
        }

        StringImpl* s = new StringImpl(*this);
        Size len = other->length();
        for (Size i = 0; i < len; i++)
            s->str_.push_back(other->charAt(i));
        CPtr p(s);
        return p;
    }

    Int compareTo(Object::CPtr that) const {
        Int result = Object::compareTo(that);
        if (result != TYPE_CMP_SAME &&
            result != -TYPE_CMP_SAME) {
            return result;
        }

        String::CPtr other = LIBJ_STATIC_CPTR_CAST(String)(that);
        Size len1 = this->length();
        Size len2 = other->length();
        Size len = len1 < len2 ? len1 : len2;
        for (Size i = 0; i < len; i++) {
            Char c1 = this->charAt(i);
            Char c2 = other->charAt(i);
            if (c1 != c2)
                return c1 - c2;
        }
        return len1 - len2;
    }

    Boolean startsWith(CPtr other, Size offset) const {
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < offset + len2)
            return false;
        for (Size i = 0; i < len2; i++)
            if (this->charAt(offset + i) != other->charAt(i))
                return false;
        return true;
    }

    Boolean endsWith(CPtr other) const {
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < len2)
            return false;
        Size pos = len1 - len2;
        for (Size i = 0; i < len2; i++)
            if (this->charAt(pos + i) != other->charAt(i))
                return false;
        return true;
    }

    Size indexOf(Char c, Size offset) const {
        Size len = length();
        for (Size i = offset; i < len; i++)
            if (charAt(i) == c)
                return i;
        return NO_POS;
    }

    Size indexOf(CPtr other, Size offset) const {
        // TODO(plenluno): make it more efficient
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < offset + len2)
            return NO_POS;
        Size n = len1 - len2 + 1;
        for (Size i = offset; i < n; i++)
            if (startsWith(other, i))
                return i;
        return NO_POS;
    }

    Size lastIndexOf(Char c, Size offset) const {
        Size len = length();
        if (len == 0)
            return NO_POS;
        for (Size i = offset < len ? offset : len-1; ; i--) {
            if (charAt(i) == c)
                return i;
            if (i == 0)
                break;
        }
        return NO_POS;
    }

    Size lastIndexOf(CPtr other, Size offset) const {
        // TODO(plenluno): make it more efficient
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < offset + len2)
            return NO_POS;
        Size from = len1 - len2;
        from = offset < from ? offset : from;
        for (Size i = from; ; i--) {
            if (startsWith(other, i))
                return i;
            if (i == 0)
                break;
        }
        return NO_POS;
    }

    Boolean isEmpty() const {
        return length() == 0;
    }

    CPtr toLowerCase() const {
        Size len = length();
        StringImpl* s = new StringImpl();
        for (Size i = 0; i < len; i++) {
            Char c = charAt(i);
            if (c >= 'A' && c <= 'Z')
                c += 'a' - 'A';
            s->str_ += c;
        }
        CPtr p(s);
        return p;
    }

    CPtr toUpperCase() const {
        Size len = length();
        StringImpl* s = new StringImpl();
        for (Size i = 0; i < len; i++) {
            Char c = charAt(i);
            if (c >= 'a' && c <= 'z')
                c -= 'a' - 'A';
            s->str_ += c;
        }
        CPtr p(s);
        return p;
    }

    CPtr toString() const {
        CPtr p(new StringImpl(*this));
        return p;
    }

    std::string toStdString() const {
        return glue::fromUtf32(str_, glue::UTF8);
    }

    std::u16string toStdU16String() const {
        return glue::utf32ToUtf16(str_);
    }

    std::u32string toStdU32String() const {
        return str_;
    }

    static CPtr create() {
        CPtr p(new StringImpl());
        return p;
    }

    static CPtr create(Char c, Size n) {
        CPtr p(new StringImpl(c, n));
        return p;
    }

    static CPtr create(const void* data, Encoding enc, Size max) {
        CPtr p (new StringImpl(data, enc, max));
        return p;
    }

    static CPtr create(const std::u32string& s32) {
        CPtr p(new StringImpl(s32));
        return p;
    }

 private:
    static glue::UnicodeEncoding convertEncoding(Encoding enc) {
        switch (enc) {
        case UTF8:
            return glue::UTF8;
        case UTF16BE:
            return glue::UTF16BE;
        case UTF16LE:
            return glue::UTF16LE;
        case UTF32BE:
            return glue::UTF32BE;
        case UTF32LE:
            return glue::UTF32LE;
        default:
            assert(false);
        }
    }

 private:
    std::u32string str_;

    StringImpl() : str_() {}

    StringImpl(Char c, Size n) : str_(n, c) {}

    StringImpl(const void* data, Encoding enc, Size max)
        : str_(glue::toUtf32(data, convertEncoding(enc), max)) {}

    StringImpl(const std::u32string& s32) : str_(s32) {}

    StringImpl(const StringImpl& other) : str_(other.str_) {}

    StringImpl(const StringImpl& other, Size pos, Size count = NO_POS)
        : str_(other.str_, pos, count) {}
};

String::CPtr String::create() {
    static const String::CPtr empty =
        StringImpl::create(NULL, UTF8, NO_POS);
    return empty;
}

String::CPtr String::create(Char c, Size n) {
    return StringImpl::create(c, n);
}

String::CPtr String::create(const void* data, Encoding enc, Size max) {
    return StringImpl::create(data, enc, max);
}

String::CPtr String::create(const std::u32string& s32) {
    return StringImpl::create(s32);
}

static String::CPtr LIBJ_STR_TRUE = String::create("true");
static String::CPtr LIBJ_STR_FALSE = String::create("false");

static String::CPtr booleanToString(const Value& val) {
    Boolean b;
    to<Boolean>(val, &b);
    return b ? LIBJ_STR_TRUE : LIBJ_STR_FALSE;
}

static String::CPtr byteToString(const Value& val) {
    Byte b;
    to<Byte>(val, &b);
    const Size kLen = (8 / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%d", b);
    return String::create(s);
}

static String::CPtr shortToString(const Value& val) {
    Short sh;
    to<Short>(val, &sh);
    const Size kLen = (16 / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%d", sh);
    return String::create(s);
}

static String::CPtr intToString(const Value& val) {
    Int i;
    to<Int>(val, &i);
    const Size kLen = (32 / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%d", i);
    String::CPtr p = String::create(s);
    return p;
}

static String::CPtr longToString(const Value& val) {
    Long l;
    to<Long>(val, &l);
    const Size kLen = (64 / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%lld", l);
    return String::create(s);
}

static String::CPtr floatToString(const Value& val) {
    Float f;
    to<Float>(val, &f);
    const Size kLen = 64;
    char s[kLen];
    return String::create(v8::internal::DoubleToCString(f, s, kLen));
}

static String::CPtr doubleToString(const Value& val) {
    Double d;
    to<Double>(val, &d);
    const Size kLen = 64;
    char s[kLen];
    return String::create(v8::internal::DoubleToCString(d, s, kLen));
}

static String::CPtr sizeToString(const Value& val) {
    Size n;
    to<Size>(val, &n);
    const Size kLen = ((sizeof(Size) << 3) / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%zd", n);
    String::CPtr p = String::create(s);
    return p;
}

static String::CPtr typeIdToString(const Value& val) {
    TypeId t;
    to<TypeId>(val, &t);
    const Size kLen = ((sizeof(TypeId) << 3) / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%zd", t);
    String::CPtr p = String::create(s);
    return p;
}

static String::CPtr objectToString(const Value& val) {
    Object::CPtr o = toCPtr<Object>(val);
    if (o) {
        return o->toString();
    } else {
        return String::null();
    }
}

String::CPtr String::valueOf(const Value& val) {
    if (val.isEmpty()) {
        return null();
    } else if (val.type() == Type<Boolean>::id()) {
        return booleanToString(val);
    } else if (val.type() == Type<Byte>::id()) {
        return byteToString(val);
    } else if (val.type() == Type<Short>::id()) {
        return shortToString(val);
    } else if (val.type() == Type<Int>::id()) {
        return intToString(val);
    } else if (val.type() == Type<Long>::id()) {
        return longToString(val);
    } else if (val.type() == Type<Float>::id()) {
        return floatToString(val);
    } else if (val.type() == Type<Double>::id()) {
        return doubleToString(val);
    } else if (val.type() == Type<Size>::id()) {
        return sizeToString(val);
    } else if (val.type() == Type<TypeId>::id()) {
        return typeIdToString(val);
    } else if (val.instanceof(Type<Object>::id())) {
        return objectToString(val);
    } else {
        return null();
    }
}

}  // namespace libj
