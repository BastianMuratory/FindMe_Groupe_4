# Bastian : Lance le programme qui change l'encodage des textes

# compile et lance le programme
run: utf8.o
	gcc -Wall -o test utf8.o
	./test

# Compile le programme
utf8.o: utf8.c
	gcc -Wall -c utf8.c

clean:
	rm -rf temp* test *.o