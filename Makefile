CC=g++-10.2
SOURCE=console_app

hellomake:
	test -d OGDF || (wget -nd http://www.stud.fit.vutbr.cz/~xpagac06/GAL/OGDF.zip && unzip OGDF.zip)
	$(CC) -static-libstdc++ -IOGDF/include -o $(SOURCE).o -c $(SOURCE).cpp -std=c++17
	$(CC) -static-libstdc++ -o gal -L./OGDF $(SOURCE).o -lOGDF -lCOIN -pthread