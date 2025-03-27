#include <iostream>
#include <fstream>
#include "stuffs.h"
using namespace std;

int main() {
    ifstream file1("/input/car.tga", ios::binary);
    char IDlength;
    file1.read(&IDlength,sizeof(IDlength));
	cout << IDlength << endl;
};