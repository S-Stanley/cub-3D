#!/bin/bash

rm -rf tests/.leaks tests/.output
mkdir tests/.leaks
touch tests/.output

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

echo -e "${NC} TEST ERRORS" >> tests/.output
echo >> tests/.output

for dir in $(ls maps/ | grep invalid); do
	var="tests/.leaks/$dir"
	valgrind --leak-check=full --show-reachable=yes --log-file=$var ./cub3D maps/"$dir" >> /dev/null
	if [ $? -eq 1 ]
	then
		echo -e "${GREEN} $dir OK" >> tests/.output;
	else
		echo -e "${RED} $dir KO" >> tests/.output;
	fi
done

echo >> tests/.output
echo -e "${NC} TESTS LEAKS" >> tests/.output
echo >> tests/.output

for dir in $(ls tests/.leaks); do
	cat "tests/.leaks/$dir" | grep "All heap blocks were freed -- no leaks are possible" >> /dev/null
	if [ $? -eq 0 ]
	then
		echo -e "${GREEN} $dir OK" >> tests/.output;
	else
		echo -e "${RED} $dir KO" >> tests/.output;
	fi
done

cat tests/.output
rm -rf tests/.leaks tests/.output