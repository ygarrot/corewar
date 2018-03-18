#!/bin/bash

MY_ASM="./asm"
CLEAN_SCRIPT="../resources/clean.sh"
GEN_SCRIPT="../resources/gen.sh"
FILES=$(find ../resources -name "*.s")

_RED="\\x1b[31m"
_GREEN="\\x1b[32m"
_YELLOW="\\x1b[33m"
_END="\\x1b[0m"

if [ ! -f ${MY_ASM} ]; then
	printf "the %s doesn't exist...\\n" "${MY_ASM}"
	printf "abort\\n"
	exit 1
fi

function switch_dir()
{
	if [ ! $# = 1 ]; then
		exit 1
	fi
	cd ../resources || exit 1
	sh "${1}"
	cd ../asm_dir || exit 1
}

switch_dir ${CLEAN_SCRIPT}

for i in ${FILES}; do
	printf "Handle %s\\n" "${i}"
	${MY_ASM} "${i}" > /dev/null 2>&1
	if [ ! $? = 0 ]; then
		printf "${_YELLOW}\\tasm problem for %s${_END}\\n" "${i}"
	else
		old_name=${i/.s/.cor}
		new_name=${i/.s/.my.cor}
		mv "${old_name}" "${new_name}"
	fi
done

switch_dir ${GEN_SCRIPT}

AVAILABLE=$(find ../resources -name "*.my.cor")

for file in ${AVAILABLE}; do
	name=${file/.my.cor/.cor}
	diff -u "${file}" "${name}" &>/dev/null
	if [ $? = 0 ]; then
		printf "${_GREEN}OK  ->\t${file}${_END}\\n"
	else
		printf "${_RED}KO  ->\t${file}${_END}\\n"
	fi
done
