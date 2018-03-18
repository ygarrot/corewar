#!/bin/bash

MY_ASM="./asm"
BASE_ASM="../resources/asm"
FILES=$(find wrong_tests -name "*.s")

_RED=$(tput setaf 1)
_PURPLE=$(tput setaf 5)
_END=$(tput sgr0)

if [ ! -f ${MY_ASM} ]; then
	printf "the %s doesn't exist...\\n" "${MY_ASM}"
	printf "abort\\n"
	exit 1
fi

for i in ${FILES}; do
	ret1=$(${MY_ASM} "${i}" 2>&1)
	ret2=$(${BASE_ASM} "${i}" 2>&1)
	color1=${_PURPLE}
	color2=${_PURPLE}
	if [[ ${ret1} = Writ* ]]; then
		color1=${_END}
	fi
	if [[ ${ret2} = Writ* ]]; then
		color2=${_END}
	fi

	printf "%s%s%s\n\t" "${_RED}" "${i}" "${color1}"
	printf "%s\n" "${ret1}"
	printf "\t%s" "${color2}"
	printf "%s\n" "${ret2}"
	printf "%s" "${_END}"
done;