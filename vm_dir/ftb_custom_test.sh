#!/bin/bash

. ftb_functions.sh

if [ ! $# = 2 ]; then
	printf "Must be called with 2 argumnets...\\n"
	printf "abort\\n"
	exit 1
fi

verifyCorewarBinary
cleanThenBuildPlayers

fight "${1}" "${2}"
