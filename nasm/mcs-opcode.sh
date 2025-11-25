#!/usr/bin/env bash

# System : Archlinux
# Architektur : _86_64
# ToolChain : sudo pacman -S nasm binutils sudo pacman -S nasm binutils
# Version : nasm -v objdump --version NASM version 3.01 compiled on Oct 13 2025 GNU objdump (GNU Binutils) 2.45.1

asmfile="$1"

if [[ -z "$asmfile" ]]; then
    echo "Nutze: mcs-opcode.sh datei.asm"
    exit 1
fi

outfile="${asmfile%.asm}.o"

nasm -felf64 "$asmfile" -o "$outfile" || exit 1
objdump -d "$outfile" | grep "^ " | awk '{print $2}'
