// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <float.h>
#include <libj/array_list.h>
#include <libj/json.h>
#include <libj/map.h>
#include <libj/null.h>

namespace libj {

TEST(GTestJson, TestStringify) {
    ASSERT_EQ(json::stringify(static_cast<Byte>(3))
        ->compareTo(String::create("3")), 0);
    ASSERT_EQ(json::stringify(static_cast<Short>(4))
        ->compareTo(String::create("4")), 0);
    ASSERT_EQ(json::stringify(static_cast<Int>(5))
        ->compareTo(String::create("5")), 0);
    ASSERT_EQ(json::stringify(static_cast<Long>(6))
        ->compareTo(String::create("6")), 0);
    ASSERT_EQ(json::stringify(static_cast<Float>(2.5))
        ->compareTo(String::create("2.5")), 0);
    ASSERT_EQ(json::stringify(static_cast<Double>(3.5))
        ->compareTo(String::create("3.5")), 0);
    ASSERT_EQ(json::stringify(DBL_MAX)
        ->compareTo(String::create("1.7976931348623157e+308")), 0);
    ASSERT_EQ(json::stringify(-DBL_MIN)
        ->compareTo(String::create("-2.2250738585072014e-308")), 0);
    ASSERT_EQ(json::stringify(true)
        ->compareTo(String::create("true")), 0);
    ASSERT_EQ(json::stringify(false)
        ->compareTo(String::create("false")), 0);
    ASSERT_EQ(json::stringify(Null::instance())
        ->compareTo(String::create("null")), 0);
    ASSERT_EQ(json::stringify(String::create("456"))
        ->compareTo(String::create("\"456\"")), 0);
    ASSERT_EQ(json::stringify(Map::create())
        ->compareTo(String::create("{}")), 0);
    ASSERT_EQ(json::stringify(ArrayList::create())
        ->compareTo(String::create("[]")), 0);

    Map::Ptr m = Map::create();
    m->put(3, false);
    m->put(String::create("x"), 123);
    m->put(String::create("y"), String::create("456"));
    ASSERT_EQ(json::stringify(m)
        ->compareTo(String::create("{\"x\":123,\"y\":\"456\"}")), 0);

    ArrayList::Ptr a = ArrayList::create();
    a->add(3);
    a->add(false);
    ASSERT_EQ(json::stringify(a)
        ->compareTo(String::create("[3,false]")), 0);
}

TEST(GTestJson, TestParse) {
    String::CPtr json = String::create("{\"x\":123,\"y\":[3.0,false]}");
    Value v = json::parse(json);
    ASSERT_TRUE(v.instanceof(Type<Map>::id()));
    Map::CPtr m = toCPtr<Map>(v);
    ASSERT_EQ(m->size(), 2);
    Value xv = m->get(String::create("x"));
    Value yv = m->get(String::create("y"));
    ASSERT_TRUE(xv.type() == Type<Long>::id());
    Long l;
    to<Long>(xv, &l);
    ASSERT_EQ(l, 123);
    ASSERT_TRUE(yv.instanceof(Type<ArrayList>::id()));
    ArrayList::CPtr a = toCPtr<ArrayList>(yv);
    Value a0 = a->get(0);
    Value a1 = a->get(1);
    ASSERT_TRUE(a0.type() == Type<Double>::id());
    Double d;
    to<Double>(a0, &d);
    ASSERT_EQ(d, 3.0);
    ASSERT_TRUE(a1.type() == Type<Boolean>::id());
    Boolean b;
    to<Boolean>(a1, &b);
    ASSERT_EQ(b, false);
}

TEST(GTestJson, TestEscape) {
    String::CPtr str = String::create("\b\t\r\n'\"\\");
    String::CPtr json = String::create("\"\\b\\t\\r\\n'\\\"\\\\\"");
    String::CPtr s = toCPtr<String>(json::parse(json));
    ASSERT_EQ(s->compareTo(str), 0);
    s = json::stringify(str);
    ASSERT_EQ(s->compareTo(json), 0);
};

}  // namespace libj
