#!/bin/bash

ASM="./asm"

FILES=$(find . -name "*.s")

_YELLOW="\\x1b[33m"
_END="\\x1b[0m"

if [ ! -f ${ASM} ]; then
	echo "the file ${ASM} does not exist..."
	echo "abort"
	exit 1
fi

for i in ${FILES}; do
	${ASM} "${i}"
	if [ ! $? = 0 ]; then
		printf "${_YELLOW}\\tasm problem for %s${_END}\\n" "${i}"
	fi
done
