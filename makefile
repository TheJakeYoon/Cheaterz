plagiarismCatcher: driver.o fileread.o Hash.o
	g++ -std=c++11  -o plagiarismCatcher driver.o fileread.o Hash.o
driver.o: driver.cpp Hash.h fileread.h
	g++ -std=c++11 -c  driver.cpp
fileread.o: fileread.cpp fileread.h
	g++ -std=c++11 -c fileread.cpp
Hash.o: Hash.cpp Hash.h
	g++ -std=c++11 -c Hash.cpp
