#!/usr/bin/env bash

# This command can be run by the user to clang-format everything.

PLATFORM=$(uname)
TOOLSPATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
CLANGFORMAT="clang-format-14 -style=file"

pushd "$TOOLSPATH" > /dev/null
CHECK_DIRS=()
for DIR in "include" "src" "tests"; do [ -d "$TOOLSPATH/../$DIR" ] && CHECK_DIRS+=("$DIR") ; done
find ${CHECK_DIRS[@]} \
    \( -name '*.cpp' -o -name '*.h' -o -name '*.cu' -o -name '*.cuh' -o -name '*.hpp' \) \
    -not -name pugi* -not -name json.hpp -not -path '*/third-party/*' \
    -print0 \
    | xargs -n1 -0 ${CLANGFORMAT} -i
popd > /dev/null