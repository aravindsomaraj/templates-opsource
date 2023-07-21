all: bin main

bin: 
	mkdir bin

main:	bin/test.o
	g++ prg.cpp test.hpp bin/test.o -o output
	mv output bin/

bin/test.o: test.cpp
	g++ -c test.cpp
	mv test.o bin/

clean: 
	rm -r bin

run: all 
	./bin/output 

