#!/bin/sh

for proj in $4; do
    $1 -C $proj DESTDIR="$(realpath $2)" PREFIX="$3" install
done
