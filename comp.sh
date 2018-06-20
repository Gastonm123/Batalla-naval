#!/bin/bash

gcc *.c -std=c99 -o prog.o 2> ERR.log


#if [ -s ERR.log ]; then
#	medit ERR.log
#else
#	chmod +x prog.o
#	./prog.o
#fi
