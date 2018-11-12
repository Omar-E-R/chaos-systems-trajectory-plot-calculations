string=$(gcc -Wall -o test.o t.c --pass-exit-codes)
if [ "$string" == "$NULL" ]; then
	echo "NULL"
else
	echo "NOT"
fi

