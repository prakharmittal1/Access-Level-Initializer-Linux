obj-y:=sysaccesslevel.o

accesslevel.o: accesslevel.c
	gcc -o accesslevel.o -c accesslevel.c
	ar cr libaccesslevel.a accesslevel.o
