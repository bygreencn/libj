// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPEDEF_H_
#define LIBJ_TYPEDEF_H_

#include <stddef.h>
#include <inttypes.h>

#ifndef LIBJ_USE_CXX11
#include <string>

namespace std {

typedef uint16_t char16_t;
typedef uint32_t char32_t;
typedef basic_string<char16_t> u16string;
typedef basic_string<char32_t> u32string;

}  // namespace std
#endif

namespace libj {

typedef bool Boolean;
typedef int8_t Byte;
typedef int16_t  Short;
typedef int32_t Int;
typedef int64_t Long;
typedef uint8_t UByte;
typedef uint16_t UShort;
typedef uint32_t UInt;
typedef uint64_t ULong;
typedef float Float;
typedef double Double;
typedef std::char16_t Char16;
typedef std::char32_t Char32;
typedef Char32 Char;
typedef size_t Size;
typedef uintptr_t TypeId;

}  // namespace libj

#endif  // LIBJ_TYPEDEF_H_
