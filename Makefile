make:
	g++ -std=c++11 -o project2.out src/main.cpp

make tasks:
	g++ -std=c++11 -o project2.out src/main.cpp
	./project2.out ./input/circles.tga multiply ./input/layer1.tga
	./project2.out ./input/layer1.tga multiply flip
	./project2.out ./input/layer1.tga subtract ./input/layer2.tga


run:
	del /F /Q project2.exe 2> NUL
	g++ -std=c++11 -o project2.exe src/main.cpp

clean:
	del /F /Q *.o project2.exe *.out 2> NUL