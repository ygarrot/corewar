#!/bin/bash

if [ ${0} = "functions.sh" -o ${0} = "./functions.sh" ]; then
	printf "SNA : Shouldn't be used like that...\\n"
	exit 1
fi

MY_VM="./corewar"
BASE_VM="../resources/corewar"
PATH_RESOURCES="../resources/"

_RED="\\x1b[31m"
_GREEN="\\x1b[32m"
_BLUE="\\x1b[94m"
_END="\\x1b[0m"

function fight()
{
	tmp1="/tmp/corewar.my_output"
	tmp2="/tmp/corewar.vm_output"
	name1=$1
	name2=$2
	if [ ! $# = 2 ]; then
		printf "You need to call this function with 2 parameters..."
		exit 1
	fi
	printf "Match versus %s // %s\\n\\t" "${name1/*\//}" "${name2/*\//}"
	${MY_VM} -show 31 "${name1}" "${name2}" > ${tmp1}
	${BASE_VM} -a -v 31 "${name1}" "${name2}" 2>&1 > ${tmp2} 
	retNormal1=$(cat ${tmp1} | tail -n 1 | grep "${name1}")
	retNormal2=$(cat ${tmp2} | tail -n 1 | grep "${name1}")
	retLarge1=$(cat ${tmp1} | grep "large")
	retLarge2=$(cat ${tmp2} | grep "large")
	if 	([ "${retLarge1}" ] && [ "${retLarge2}" ]) || ([ -z "${retLarge1}" ] && [ -z "${retLarge2}" ]) &&
		([ "${retNormal1}" ] && [ "${retNormal2}" ]) ||
		([ -z "${retNormal1}" ] && [ -z "${retNormal2}" ]); then
		printf "${_GREEN}Same results${_END}"
	else
		printf "${_RED}results differed${_END}"
	fi
	retFinal=$(diff -u ${tmp1} ${tmp2})
	printf "\\n${_BLUE}"
	printf "%s" "${retFinal}"
	if [ -z "${retFinal}" ]; then
		printf "\tNo diff in verbose output"
	fi
	printf "${_END}"
	printf "\\n"
}

function verifyCorewarBinary()
{
	if [ ! -f ${MY_VM} ]; then
		printf "The file %s doesn't to exist\\n" "${MY_VM}"
		printf "abort\\n"
		exit 1
	fi
}

function cleanThenBuildPlayers()
{
	cd ${PATH_RESOURCES} || exit 1
	bash ./clean.sh
	bash ./gen.sh
	cd ../vm_dir || exit 1
}
