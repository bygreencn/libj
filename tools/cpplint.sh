#!/bin/sh
tools/cpplint/cpplint.py --filter=-runtime/explicit,-readability/streams `find include src btest gtest -type f`
