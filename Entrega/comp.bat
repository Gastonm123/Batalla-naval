@echo off
gcc *.c -std=c99 -o prog.exe
start /d "." prog.exe
