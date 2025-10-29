#!/bin/sh

dir=$(basename $(pwd))

if [ "$dir" != "libc" ]; then
    cat > .clangd <<EOF
CompileFlags:
    Add: [-xc, -I$(pwd)/include, -I$(realpath "$(pwd)/../libc/include"), -nostdinc]
EOF
else
    cat > .clangd <<EOF
CompileFlags:
    Add: [-xc, -I$(pwd)/include, -nostdinc]
EOF
fi
