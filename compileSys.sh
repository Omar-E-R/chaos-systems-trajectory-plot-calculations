LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
export LD_LIBRARY_PATH
read cmd
gcc -Wall -c $cmd.c -o $cmd.o -I./include
gcc -Wall $cmd.o -L./lib -ltrajectoire -o $cmd
./$cmd
exit