#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor; 
};

struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

struct Image {
    Header header;
    vector<Pixel> pixels;
};

Image ReadPic(const string& ipath) {
    ifstream tga(ipath, ios::binary);
    Image img;

    if (!tga.is_open()) {
        cerr << "file not open" << endl;
        return img;
    }

    Header head;

    tga.read(reinterpret_cast<char*>(&head.idLength), sizeof(head.idLength));
    tga.read(reinterpret_cast<char*>(&head.colorMapType), sizeof(head.colorMapType));
    tga.read(reinterpret_cast<char*>(&head.dataTypeCode), sizeof(head.dataTypeCode));
    tga.read(reinterpret_cast<char*>(&head.colorMapOrigin), sizeof(head.colorMapOrigin));
    tga.read(reinterpret_cast<char*>(&head.colorMapLength), sizeof(head.colorMapLength));
    tga.read(reinterpret_cast<char*>(&head.colorMapDepth), sizeof(head.colorMapDepth));
    tga.read(reinterpret_cast<char*>(&head.xOrigin), sizeof(head.xOrigin));
    tga.read(reinterpret_cast<char*>(&head.yOrigin), sizeof(head.yOrigin));
    tga.read(reinterpret_cast<char*>(&head.width), sizeof(head.width));
    tga.read(reinterpret_cast<char*>(&head.height), sizeof(head.height));
    tga.read(reinterpret_cast<char*>(&head.bitsPerPixel), sizeof(head.bitsPerPixel));
    tga.read(reinterpret_cast<char*>(&head.imageDescriptor), sizeof(head.imageDescriptor));

    img.header = head;

    int pixelnum = head.height * head.width;

    if (pixelnum <= 0) {
        cerr << "dimensions invalid" << endl;
    }

    for (int i = 0; i < pixelnum; i++) {
        Pixel pixel;
        tga.read(reinterpret_cast<char*>(&pixel.blue), sizeof(pixel.blue));
        tga.read(reinterpret_cast<char*>(&pixel.green), sizeof(pixel.green));
        tga.read(reinterpret_cast<char*>(&pixel.red), sizeof(pixel.red));

        img.pixels.push_back(pixel);
    }

    tga.close();
    return img;
};

void WritePic(Image& img, const string& opath) {
    ofstream oimg(opath, ios::binary);

    if (!oimg.is_open()) {
        cerr << "file not open" << endl;
    }

    oimg.write(reinterpret_cast<char*>(&img.header.idLength), sizeof(img.header.idLength));
    oimg.write(reinterpret_cast<char*>(&img.header.colorMapType), sizeof(img.header.colorMapType));
    oimg.write(reinterpret_cast<char*>(&img.header.dataTypeCode), sizeof(img.header.dataTypeCode));
    oimg.write(reinterpret_cast<char*>(&img.header.colorMapOrigin), sizeof(img.header.colorMapOrigin));
    oimg.write(reinterpret_cast<char*>(&img.header.colorMapLength), sizeof(img.header.colorMapLength));
    oimg.write(reinterpret_cast<char*>(&img.header.colorMapDepth), sizeof(img.header.colorMapDepth));
    oimg.write(reinterpret_cast<char*>(&img.header.xOrigin), sizeof(img.header.xOrigin));
    oimg.write(reinterpret_cast<char*>(&img.header.yOrigin), sizeof(img.header.yOrigin));
    oimg.write(reinterpret_cast<char*>(&img.header.width), sizeof(img.header.width));
    oimg.write(reinterpret_cast<char*>(&img.header.height), sizeof(img.header.height));
    oimg.write(reinterpret_cast<char*>(&img.header.bitsPerPixel), sizeof(img.header.bitsPerPixel));
    oimg.write(reinterpret_cast<char*>(&img.header.imageDescriptor), sizeof(img.header.imageDescriptor));

    for (int i = 0; i < img.header.width * img.header.height; i++) {
        Pixel currPix = img.pixels[i];
        unsigned char cblue = currPix.blue;
        unsigned char cgreen = currPix.green;
        unsigned char cred = currPix.red;

        oimg.write(reinterpret_cast<char*>(&cblue),sizeof(cblue));
        oimg.write(reinterpret_cast<char*>(&cgreen),sizeof(cgreen));
        oimg.write(reinterpret_cast<char*>(&cred),sizeof(cred));

    }
    
    oimg.close();
};

int main() {
    // string path = "input/car.tga";
    // Image img = ReadPic(path);
    // string outpath = "output/task1.tga";
    // WritePic(img, outpath);
    // cout << "beans" << endl;

    return 0;
};