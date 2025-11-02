#!/bin/sh

dir=$(basename $(pwd))

includes=""

for include in $@; do
    includes="$includes, -I$(realpath "$(pwd)/../$include/include")"
done

cat > .clangd <<EOF
CompileFlags:
    Add: [-xc, -I$(pwd)/include $includes, -nostdinc]
EOF
