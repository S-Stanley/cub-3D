rm -rf tests/.leaks
rm tests/.output
mkdir tests/.leaks
touch tests/.output

echo "TEST ERRORS" >> tests/.output

for dir in $(ls maps/ | grep invalid); do
	var="tests/.leaks/$dir"
	valgrind --leak-check=full --show-reachable=yes --log-file=$var ./cub3D maps/"$dir"
	if [ $? -eq 1 ]
	then
		echo "$dir OK" >> tests/.output;
	else
		echo "$dir KO" >> tests/.output;
	fi
done

echo "TESTS LEAKS" >> tests/.output

for dir in $(ls tests/.leaks); do
	cat tests/.leaks/invaliddddd.cubbbbbb | grep "All heap blocks were freed -- no leaks are possible"
	if [ $? -eq 0 ]
	then
		echo "$dir OK" >> tests/.output;
	else
		echo "$dir KO" >> tests/.output;
	fi
done