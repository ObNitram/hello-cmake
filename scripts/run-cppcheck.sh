#!/bin/bash

cppcheck --enable=all --inconclusive --std=c++20 --suppress=missingIncludeSystem \
--checkers-report=cppcheck-report.log \
src/
