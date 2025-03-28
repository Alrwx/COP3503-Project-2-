make:
	g++ -std=c++11 -o project2.out src/main.cpp

run:
	g++ -std=c++11 -o project2.exe src/main.cpp
	./project2.exe

test:
	g++ -std=c++11 -o test.exe src/test.cpp
	./test.exe

clean:
	del /F /Q *.o project2.exe test.exe 2> NUL