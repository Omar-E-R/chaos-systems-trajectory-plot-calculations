LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
export LD_LIBRARY_PATH
read cmd
gcc -Wall -I./include $cmd.c -L./lib -ltrajectoire -o $cmd
./$cmd
exit