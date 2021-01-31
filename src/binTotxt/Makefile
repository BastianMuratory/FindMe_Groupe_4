# Bastian : Makefile pour compiler le programe de traduction des fichiers bnaires 

# compile et lance le programme
run: binTotxt.o
	gcc -Wall -o binTotxt.exe binTotxt.o
	./binTotxt.exe

# Compile le programme
binTotxt.o: binTotxt.c
	gcc -Wall -c binTotxt.c

clean:
	rm -rf temp* *.o