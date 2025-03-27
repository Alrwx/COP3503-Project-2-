build:
	g++ -o project2.out src/main.cpp

run:
	g++ -o project2.exe src/main.cpp
	./project2.exe

test:
	g++ -o test.exe src/test.cpp
	./test.exe

clean:
	del /F /Q *.o project2.exe test.exe 2> NUL