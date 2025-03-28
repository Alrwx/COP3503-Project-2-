make:
	g++ -std=c++11 -o project2.out src/main.cpp

run:
	g++ -std=c++11 -o project2.exe src/main.cpp

clean:
	del /F /Q *.o project2.exe 2> NUL