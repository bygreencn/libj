#!/bin/sh
tools/cpplint/cpplint.py --filter=-runtime/explicit,-runtime/references,-readability/streams,-build/include_what_you_use --prefix=libj `find include src btest gtest -type f`
