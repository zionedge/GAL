CC=g++
TARGET=console_app

hellomake: ./OGDF/doc/examples/basic/manual.cpp
	$(CC) -IOGDF/include -o $(TARGET).o -c $(TARGET).cpp -std=c++17
	$(CC) -o gal -L./OGDF $(TARGET).o -lOGDF -lCOIN -pthread