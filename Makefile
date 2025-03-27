build:
	g++ -o project2.exe src/main.cpp
	./project2.exe

test:
	g++ -o test.exe src/test.cpp
	./test.exe

clean:
	rm project2.exe