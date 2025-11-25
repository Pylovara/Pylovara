#!/usr/bin/env bash

input="$1"

while read -r line; do
    set -- $line
    cmd="$1"
    arg="$2"

    case "$cmd" in
        proton|PROTON)
            printf "48 c7 c0 %02x 00 00 00\n" "$arg"
        ;;
    esac
done < "$input"
