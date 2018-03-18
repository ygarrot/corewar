#!/bin/bash

. ftb_functions.sh

verifyCorewarBinary
cleanThenBuildPlayers

SIMPLE_FILES="../resources/champs/examples/zork.cor"
SIMPLE_FILES=${SIMPLE_FILES}" ../resources/champs/toto.cor"
SIMPLE_FILES=${SIMPLE_FILES}" ../resources/champs/championships/2014/sbuono/Asombra.cor"
SIMPLE_FILES=${SIMPLE_FILES}" ../resources/champs/championships/2017/nolivier/run_Kitty_RUN.cor"
SIMPLE_FILES=${SIMPLE_FILES}" ../resources/champs/championships/2017/adenis/Explosive_Kitty.cor"
SIMPLE_FILES=${SIMPLE_FILES}" ../resources/champs/championships/2017/agregoir/Kittystrophic.cor"
SIMPLE_FILES=${SIMPLE_FILES}" ../resources/champs/championships/2017/gnebie/ultima.cor"
SIMPLE_FILES=${SIMPLE_FILES}" ../resources/champs/championships/2017/iburel/gateau.cor"
SIMPLE_FILES=${SIMPLE_FILES}" ../resources/champs/championships/2017/nolivier/run_Kitty_RUN.cor"
SIMPLE_FILES=${SIMPLE_FILES}" ../resources/champs/championships/2017/pzarmehr/overwatch.cor"
SIMPLE_FILES=${SIMPLE_FILES}" ../resources/champs/championships/2017/tbillard/Douceur_power.cor"

for i in ${SIMPLE_FILES}; do
	for j in ${SIMPLE_FILES}; do
		fight "${i}" "${j}"
	done
done
