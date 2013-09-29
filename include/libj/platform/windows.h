// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_PLATFORM_WINDOWS_H_
#define LIBJ_PLATFORM_WINDOWS_H_

#include <direct.h>
#include <float.h>
#include <WinSock2.h>
#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define __func__ __FUNCTION__

#define getcwd _getcwd

#define usleep(useconds) Sleep(useconds/1000)

#ifndef snprintf
#define snprintf(s, n, f, ...) _snprintf_s(s, n, _TRUNCATE, f, __VA_ARGS__)
#endif

namespace std {
    inline bool isinf(double x) {
        return !!(_fpclass(x) & (_FPCLASS_PINF | _FPCLASS_NINF));
    }

    inline bool isnan(double x) {
        return !!_isnan(x);
    }

    inline bool signbit(double x) {
        return (_fpclass(x) & _FPCLASS_NZ) || x < 0;
    }
}

#endif  // LIBJ_PLATFORM_WINDOWS_H_
