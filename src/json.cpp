// Copyright (c) 2012 Plenluno All rights reserved.

#include <sstream>

#include "libj/error.h"
#include "json/json.h"
#include "libj/json.h"
#include "libj/js_array.h"
#include "libj/js_function.h"
#include "libj/js_object.h"
#include "libj/null.h"
#include "libj/string_buffer.h"
#include "libj/undefined.h"

namespace libj {
namespace json {

static Json::Reader jsonReader;

static Value toLibjValue(const Json::Value& val) {
    if (val.isNull()) {
        return Null::instance();
    } else if (val.isBool()) {
        return val.asBool();
    } else if (val.isInt()) {
        Long i = val.asInt();
        return i;
    } else if (val.isUInt()) {
        Long u = val.asUInt();
        return u;
    } else if (val.isDouble()) {
        return val.asDouble();
    } else if (val.isString()) {
        return String::create(val.asCString(), String::UTF8);
    } else if (val.isArray()) {
        JsArray::Ptr a = JsArray::create();
        Size len = val.size();
        for (Size i = 0; i < len; i++) {
            a->add(toLibjValue(val[static_cast<Json::UInt>(i)]));
        }
        return a;
    } else if (val.isObject()) {
        JsObject::Ptr jo = JsObject::create();
        Json::Value::Members ms = val.getMemberNames();
        Size len = ms.size();
        for (Size i = 0; i < len; i++) {
            String::CPtr k = String::create(ms[i].c_str());
            Value v = toLibjValue(val[ms[i]]);
            jo->put(k, v);
        }
        return jo;
    } else {
        return Undefined::instance();
    }
}

Value parse(String::CPtr str) {
    Json::Value root;
    std::istringstream is(str->toStdString());
    if (jsonReader.parse(is, root))
        return toLibjValue(root);
    else
        return Error::create(Error::ILLEGAL_ARGUMENT);
}

static const String::CPtr JSON_NULLP(static_cast<String*>(0));
static const String::CPtr JSON_NULL = String::create("null");
static const String::CPtr JSON_COLON = String::create(":");
static const String::CPtr JSON_COMMA = String::create(",");
static const String::CPtr JSON_DQUOTE = String::create("\"");
static const String::CPtr JSON_LBRACKET = String::create("[");
static const String::CPtr JSON_RBRACKET = String::create("]");
static const String::CPtr JSON_LBRACE = String::create("{");
static const String::CPtr JSON_RBRACE = String::create("}");
static const String::CPtr JSON_BSLASH = String::create("\\");
static const String::CPtr JSON_LF = String::create("\\n");
static const String::CPtr JSON_CR = String::create("\\r");
static const String::CPtr JSON_TAB = String::create("\\t");
static const String::CPtr JSON_BSPACE = String::create("\\b");

static String::CPtr stringToJson(const Value& val) {
    String::CPtr s = toCPtr<String>(val);
    StringBuffer::Ptr result = StringBuffer::create();
    result->append(JSON_DQUOTE);
    for (Size i = 0; i < s->length(); i++) {
        Char c = s->charAt(i);
        switch (c) {
        case '\b':
            result->append(JSON_BSPACE);
            break;
        case '\t':
            result->append(JSON_TAB);
            break;
        case '\n':
            result->append(JSON_LF);
            break;
        case '\r':
            result->append(JSON_CR);
            break;
        case '"':
            result->append(JSON_BSLASH);
            result->append(JSON_DQUOTE);
            break;
        case '\\':
            result->append(JSON_BSLASH);
            result->append(JSON_BSLASH);
            break;
        case '\0':
        case '\v':
            return JSON_NULLP;
        default:
            result->append(String::create(c));
        }
    }
    result->append(JSON_DQUOTE);
    return result->toString();
}

static String::CPtr mapToJson(const Value& val) {
    Map::CPtr m = toCPtr<Map>(val);
    Set::CPtr ks = m->keySet();
    Iterator::Ptr itr = ks->iterator();
    StringBuffer::Ptr result = StringBuffer::create();
    result->append(JSON_LBRACE);
    while (itr->hasNext()) {
        Value v = itr->next();
        if (v.instanceof(Type<String>::id())) {
            if (result->length() > 1)
                result->append(JSON_COMMA);
            result->append(stringToJson(v));
            result->append(JSON_COLON);
            result->append(json::stringify(m->get(v)));
        }
    }
    result->append(JSON_RBRACE);
    return result->toString();
}

static String::CPtr collectionToJson(const Value& val) {
    Collection::CPtr a = toCPtr<Collection>(val);
    Iterator::Ptr itr = a->iterator();
    StringBuffer::Ptr result = StringBuffer::create();
    result->append(JSON_LBRACKET);
    while (itr->hasNext()) {
        Value v = itr->next();
        if (result->length() > 1)
            result->append(JSON_COMMA);
        result->append(json::stringify(v));
    }
    result->append(JSON_RBRACKET);
    return result->toString();
}

String::CPtr stringify(const Value& val) {
    if (val.instanceof(Type<String>::id())) {
        return stringToJson(val);
    } else if (val.instanceof(Type<Map>::id())) {
        return mapToJson(val);
    } else if (val.instanceof(Type<Collection>::id())) {
        return collectionToJson(val);
    } else if (val.instanceof(Type<Object>::id())) {
        return JSON_NULL;
    } else {
        return String::valueOf(val);
    }
}

}  // namespace json
}  // namespace libj
