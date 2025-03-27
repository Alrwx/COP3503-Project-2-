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

    void Info() {
        cout << "id Length: " << (int)idLength << endl;
        cout << "colorMapType: " << colorMapType << endl;
        cout << "dataTypeCode: " << dataTypeCode << endl;
        cout << "colorMapOrigin: " << colorMapOrigin << endl;
        cout << "colorMapLength: " << colorMapLength << endl;
        cout << "colorMapDepth: " << colorMapDepth << endl;
        cout << "xOrigin: " << xOrigin << endl;
        cout << "yOrigin: " << yOrigin << endl;
        cout << "width: " << width << endl;
        cout << "height: " << height << endl;
        cout << "bitsPerPixel: " << bitsPerPixel << endl;
        cout << "imageDescriptor: " << imageDescriptor << endl;
        cout << endl;
    }
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
        cerr << "file not open buruhs" << endl;
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

Image multiply(Image& img1, Image& img2) {
    //normalizing the pixels
    Image nImg;

    nImg.header = img1.header;

    for (int i = 0; i < (img1.header.height * img1.header.width); i++) {

        float fblue1 = img1.pixels[i].blue / (float)255;
        float fgreen1 = img1.pixels[i].green / (float)255;
        float fred1 = img1.pixels[i].red / (float)255;

        float fblue2 = img2.pixels[i].blue / (float)255;
        float fgreen2 = img2.pixels[i].green / (float)255;
        float fred2 = img2.pixels[i].red / (float)255;

        Pixel newPix;
        int nblue = (int)((fblue1 * fblue2 * 255) + 0.5);
        newPix.blue = nblue;
        int ngreen = (int)((fgreen1 * fgreen2 * 255) + 0.5);
        newPix.green = ngreen;
        int nred = (int)((fred1 * fred2 * 255) + 0.5);
        newPix.red = nred;

        nImg.pixels.push_back(newPix);
    }

    return nImg;
};

int main() {
    // string path1 = "examples/EXAMPLE_part1.tga";
    // Image img = ReadPic(path1);
    // cout << "examples!!!" << endl;
    // img.header.Info();
    // cout << endl;

    // string path2 = "input/pattern1.tga";
    // Image img1 = ReadPic(path2);
    // cout << "layer1!!!" << endl;
    // img1.header.Info();
    // cout << endl;


    //part 1.
    string part1Path1 = "input/layer1.tga";
    Image part1Img1 = ReadPic(part1Path1);
    string part1Path2 = "input/pattern1.tga";
    Image part1Img2 = ReadPic(part1Path2);

    Image part1Img = multiply(part1Img1, part1Img2);
    WritePic(part1Img, "output/task1.tga");

    // string outpath = "output/.tga";
    // WritePic(img, outpath);
    // cout << "beans" << endl;

    // return 0;
};