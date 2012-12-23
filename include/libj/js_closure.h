// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_CLOSURE_H_
#define LIBJ_JS_CLOSURE_H_

#include <libj/js_function.h>

namespace libj {

typedef std::function<Value(JsArray::Ptr)> JsLambda;

class JsClosure : LIBJ_JS_FUNCTION(JsClosure)
 public:
    static Ptr create(JsLambda lambda);
};

}  // namespace libj

#endif  // LIBJ_JS_CLOSURE_H_
