#!/bin/sh

for proj in $2; do
    $1 -C $proj clean
done
