#!/bin/bash

set -e

find src test benchmark \( -name '*.cpp' -o -name '*.hpp' \) -exec clang-format -i {} +
