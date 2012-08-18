// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/singleton.h>
#include <libj/string.h>

namespace libj {

class GTestSingleton : LIBJ_SINGLETON(GTestSingleton)
 public:
    String::CPtr toString() const {
        return String::create("GTestSingleton");
    }
};

class GTestSingletonX {
 public:
    virtual ~GTestSingletonX() {}
    virtual int x() { return 0; }
};

TEST(GTestSingleton, Test) {
    // check EBCO
    ASSERT_EQ(sizeof(GTestSingleton), sizeof(GTestSingletonX));
}

TEST(GTestSingleton, Test2) {
    // no build errors
    GTestSingleton::Ptr p = GTestSingleton::instance();
    Singleton::Ptr p2 = p;
    Singleton::CPtr p3 = p;
    Object::CPtr p4(p);
    ASSERT_TRUE(p && p2 && p3 && p4);
}

TEST(GTestSingleton, Test3) {
    GTestSingleton::Ptr p = GTestSingleton::instance();
    ASSERT_TRUE(p->instanceof(Type<GTestSingleton>::id()));
    ASSERT_TRUE(p->instanceof(Type<Singleton>::id()));
    ASSERT_TRUE(p->instanceof(Type<Object>::id()));
}

#ifdef LIBJ_USE_SP
class GTestSingleton2 : public SingletonTmpl<GTestSingleton2> {
 public:
    TypeId type() const {
        return Type<GTestSingleton2>::id();
    }

    String::CPtr toString() const {
        return String::create("GTestSingleton2");
    }

    static int count;

 private:
    friend class SingletonTmpl<GTestSingleton2>;
    GTestSingleton2() : SingletonTmpl<GTestSingleton2>() { count++; }
    ~GTestSingleton2() { count--; }
};

int GTestSingleton2::count = 0;

TEST(GTestSingleton, Test4) {
    {
        GTestSingleton2::Ptr p = GTestSingleton2::instance();
        ASSERT_EQ(1, p.use_count());
        ASSERT_EQ(1, GTestSingleton2::count);

        GTestSingleton2::Ptr p2 = GTestSingleton2::instance();
        ASSERT_EQ(1, p.use_count());
        ASSERT_EQ(1, GTestSingleton2::count);

        p = p2;
        ASSERT_EQ(2, p.use_count());
        ASSERT_EQ(2, p2.use_count());
        ASSERT_EQ(1, GTestSingleton2::count);
    }
    ASSERT_EQ(1, GTestSingleton2::count);
}
#endif

}  // namespace libj
