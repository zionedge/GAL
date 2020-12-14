CC=c++
TARGET=

hellomake: ./OGDF/doc/examples/basic/manual.cpp
	$(CC) -IOGDF/include -o $(TARGET).o -c $(TARGET).cpp
	$(CC) -o gal -L./OGDF $(TARGET).o -lOGDF -lCOIN -pthread