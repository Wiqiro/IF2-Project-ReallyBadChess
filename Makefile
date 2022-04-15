all:
	gcc main.c  -Werror -Wall -o  main

run:
	export.bat main.exe
