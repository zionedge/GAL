CC=c++

hellomake: ./OGDF/doc/examples/basic/manual.cpp
	$(CC) -IOGDF/include -o main.o -c main.cpp
	$(CC) -o gal -L./OGDF main.o -lOGDF -lCOIN -pthread