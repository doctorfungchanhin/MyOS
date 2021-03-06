#!/bin/bash

set -o errexit

if [ -z "$1" ]; then
    echo "Target directory must not be empty"
    exit 1
fi

BUILD_DIR="$1"

rm -f "${BUILD_DIR}/myos.img"
cp myos.img "${BUILD_DIR}"

cd "${BUILD_DIR}"

mcopy -i myos.img kernel/kernel ::/boot/kernel.bin
mcopy -i myos.img user/letter1 ::/LETTER1.EXE
mcopy -i myos.img user/letter2 ::/LETTER2.EXE
mcopy -i myos.img user/letter3 ::/LETTER3.EXE
mcopy -i myos.img user/letter4 ::/LETTER4.EXE
mcopy -i myos.img KernelProcess/kerp ::/KERP.EXE
#mcopy -i myos.img apps/welcome ::/WELCOME.EXE
