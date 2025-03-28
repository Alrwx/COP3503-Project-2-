#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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
        cerr << "file " << ipath << " not open buruhs" << endl;
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

Image multiply(Image& img1, unsigned int num, string channel) {
    Image nImg;

    nImg.header = img1.header;
    // cout << num << channel << endl;
    for (int i = 0; i < (img1.header.height * img1.header.width); i++) {

        Pixel newPix;

        newPix.blue = img1.pixels[i].blue;
        newPix.green = img1.pixels[i].green;
        newPix.red = img1.pixels[i].red;

        float fblue1 = img1.pixels[i].blue / (float)255;
        float fgreen1 = img1.pixels[i].green / (float)255;
        float fred1 = img1.pixels[i].red / (float)255;

        if (channel == "blue") {
            if (((int)((fblue1 * num * 255) + 0.5)) >= 255) {
                newPix.blue = 255;
            } else if (num == 0) {
                newPix.blue = 0;
            } else {
                newPix.blue = (int)((fblue1 * num * 255) + 0.5);
            }
        } else if (channel == "green") {
            if (((int)((fgreen1 * num * 255) + 0.5)) >= 255) {
                newPix.green = 255;
            } else if (num == 0) {
                newPix.green = 0;
            } else {
                newPix.green = (int)((fgreen1 * num * 255) + 0.5);
            }
        } else if (channel == "red") {
            if (((int)((fred1 * num * 255) + 0.5)) >= 255) {
                newPix.red = 255;
            } else if (num == 0) {
                newPix.red = 0;
            } else {
                newPix.red = (int)((fred1 * num * 255) + 0.5);
            }
        }

        nImg.pixels.push_back(newPix);
    }
    // cout << (int)nImg.pixels[90].red << endl;
    
    return nImg;
};

Image subtract(Image& img1, Image& img2) {

    Image nImg;

    nImg.header = img1.header;

    for (int i = 0; i < (img1.header.height * img1.header.width); i++) {

        float fblue1 = img1.pixels[i].blue;
        float fgreen1 = img1.pixels[i].green;
        float fred1 = img1.pixels[i].red;

        float fblue2 = img2.pixels[i].blue;
        float fgreen2 = img2.pixels[i].green;
        float fred2 = img2.pixels[i].red;

        Pixel newPix;
        if ((fblue1 - fblue2) <= 0) {
            newPix.blue = 0;
        } else {
            newPix.blue = fblue1 - fblue2;
        }

        if ((fgreen1 - fgreen2) <= 0) {
            newPix.green = 0;
        } else {
            newPix.green = fgreen1 - fgreen2;
        }

        if ((fred1 - fred2) <= 0) {
            newPix.red = 0;
        } else {
            newPix.red = fred1 - fred2;
        }

        nImg.pixels.push_back(newPix);
    }

    return nImg;
};

Image screen(Image& img1, Image& img2) {
    Image nImg;
    nImg.header = img1.header;

    for (int i = 0; i < img1.header.height * img1.header.width; i++ ) {
        Pixel newPix;
        // first bracket
        float fblue1 = 1 - (img1.pixels[i].blue / (float)255);
        float fgreen1 = 1 - (img1.pixels[i].green / (float)255);
        float fred1 = 1 - (img1.pixels[i].red / (float)255);

        //second bracket
        float fblue2 = 1 - (img2.pixels[i].blue / (float)255);
        float fgreen2 = 1 - (img2.pixels[i].green / (float)255);
        float fred2 = 1 - (img2.pixels[i].red / (float)255);

        //totaling
        float nblue = (1 - (fblue1 * fblue2));
        newPix.blue = (int)((nblue * 255) + 0.5);
        float ngreen = (1 - (fgreen1 * fgreen2));
        newPix.green = (int)((ngreen * 255) + 0.5);
        float nred = (1 - (fred1 * fred2));
        newPix.red = (int)((nred * 255) + 0.5);

     
        nImg.pixels.push_back(newPix);
    }
    return nImg;
};

Image add(Image& img1, Image& img2) {
    Image nImg;

    nImg.header = img1.header;

    for (int i = 0; i < (img1.header.height * img1.header.width); i++) {

        float fblue1 = img1.pixels[i].blue;
        float fgreen1 = img1.pixels[i].green;
        float fred1 = img1.pixels[i].red;

        float fblue2 = img2.pixels[i].blue;
        float fgreen2 = img2.pixels[i].green;
        float fred2 = img2.pixels[i].red;

        Pixel newPix;
        if ((fblue1 + fblue2) >= 255) {
            newPix.blue = 255;
        } else {
            newPix.blue = fblue1 + fblue2;
        }

        if ((fgreen1 + fgreen2) >= 255) {
            newPix.green = 255;
        } else {
            newPix.green = fgreen1 + fgreen2;
        }

        if ((fred1 + fred2) >= 255) {
            newPix.red = 255;
        } else {
            newPix.red = fred1 + fred2;
        }

        nImg.pixels.push_back(newPix);
    }

    return nImg;
};

Image add(Image& img1, unsigned int num, string channel) {

    Image nImg;

    nImg.header = img1.header;

    for (int i = 0; i < (img1.header.height * img1.header.width); i++) {
        float fblue1 = img1.pixels[i].blue;
        float fgreen1 = img1.pixels[i].green;
        float fred1 = img1.pixels[i].red;

        Pixel newPix;

        newPix.blue = img1.pixels[i].blue;
        newPix.green = img1.pixels[i].green;
        newPix.red = img1.pixels[i].red;

        if (channel == "blue") {
            if ((fblue1 + num) >= 255) {
                newPix.blue = 255;
            } else {
                newPix.blue = fblue1 + num;
            }
        } else if (channel == "green") {
            if ((fgreen1 + num) >= 255) {
                newPix.green = 255;
            } else {
                newPix.green = fgreen1 + num;
            }
        } else if (channel == "red") {

            if ((fred1 + num) >= 255) {
                newPix.red = 255;
            } else {
                newPix.red = fred1 + num;
            }
        } else {
            if ((fblue1 + num) >= 255) {
                newPix.blue = 255;
            } else {
                newPix.blue = fblue1 + num;
            }
    
            if ((fgreen1 + num) >= 255) {
                newPix.green = 255;
            } else {
                newPix.green = fgreen1 + num;
            }
    
            if ((fred1 + num) >= 255) {
                newPix.red = 255;
            } else {
                newPix.red = fred1 + num;
            }
        }

        nImg.pixels.push_back(newPix);
    }

    return nImg;
};

Image overlay(Image& img1, Image& img2) {
    Image nImg;

    nImg.header = img1.header;
    for (int i = 0; i < img1.header.height * img1.header.width; i++) {
        Pixel newPix;
        
        //normalize im1
        float fblue1 = img1.pixels[i].blue / (float)255;
        float fgreen1 = img1.pixels[i].green / (float)255;
        float fred1 = img1.pixels[i].red / (float)255;

        //normalize iomg2
        float fblue2 = img2.pixels[i].blue / (float)255;
        float fgreen2 = img2.pixels[i].green / (float)255;
        float fred2 = img2.pixels[i].red / (float)255;

        if (fblue2 <= 0.5) {
            float nblue = 2 * fblue2 * fblue1;
            if (((int)((nblue * 255) + 0.5)) >= 255) {
                newPix.blue = 255;
            } else if ((int)((nblue * 255) + 0.5) <= 0) {
                newPix.blue = 0;
            } else {
                newPix.blue = (int)((nblue * 255) + 0.5);
            }
        } else if (fblue2 > 0.5) {
            float nblue = 1 - (2 * (1 - fblue1) * (1- fblue2));
            if ((int)((nblue * 255) + 0.5) >= 255) {
                newPix.blue = 255;
            }
            else if ((int)((nblue * 255) + 0.5) <= 0) {
                newPix.blue = 0;
            } else {
                newPix.blue = (int)((nblue * 255) + 0.5);
            }
        }

        if (fgreen2 <= 0.5) {
            float ngreen = 2 * fgreen2 * fgreen1;
            if ((int)((ngreen * 255) + 0.5) >= 255) {
                newPix.green = 255;
            } else if ((int)((ngreen * 255) + 0.5) <= 0) {
                newPix.green = 0;
            } else {
                newPix.green = (int)((ngreen * 255) + 0.5);
            }
        } else if (fgreen2 > 0.5) {
            float ngreen = 1 - (2 * (1 - fgreen1) * (1- fgreen2));
            if ((int)((ngreen * 255) + 0.5) >= 255) {
                newPix.green = 255;
            } else if ((int)((ngreen * 255) + 0.5) <= 0) {
                newPix.green = 0;
            } else {
                newPix.green = (int)((ngreen * 255) + 0.5);
            }
        } 


        if (fred2 <= 0.5) {
            float nred = 2 * fred2 * fred1;
            if ((int)((nred * 255) + 0.5) >= 255) {
                newPix.red = 255;
            } else if ((int)((nred * 255) + 0.5) <= 0) {
                newPix.red = 0;
            } else {
                newPix.red = (int)((nred * 255) + 0.5);
            }
        } else if (fred2 > 0.5) {
            float nred = 1 - (2 * (1 - fred1) * (1- fred2));
            if ((int)((nred * 255) + 0.5) >= 255) {
                newPix.red = 255;
            } else if ((int)((nred * 255) + 0.5) <= 0) {
                newPix.red = 0;
            } else {
                newPix.red = (int)((nred * 255) + 0.5);
            }
        }

        nImg.pixels.push_back(newPix);
    }
    return nImg;
}

Image onlyColor(Image& img, string color) {
    Image nImg;

    nImg.header = img.header;

    for (int i = 0; i < img.header.height * img.header.width; i++) {
        Pixel newPix;

        if (color == "red") {
            newPix.blue = img.pixels[i].red;
            newPix.green = img.pixels[i].red;
            newPix.red = img.pixels[i].red;
        } else if (color == "green") {
            newPix.blue = img.pixels[i].green;
            newPix.green = img.pixels[i].green;
            newPix.red = img.pixels[i].green;
        } else {
            newPix.blue = img.pixels[i].blue;
            newPix.green = img.pixels[i].blue;
            newPix.red = img.pixels[i].blue;
        }

        nImg.pixels.push_back(newPix);
    }
    // cout << nImg.pixels[100].blue << ", " << nImg.pixels[100].green << ", " << nImg.pixels[100].red << endl;
    return nImg;
}

Image combine(Image& red, Image& green, Image& blue) {

    Image nImg;

    nImg.header = red.header;

    for (int i = 0; i < red.header.width * red.header.height; i++) {
        Pixel newPix;

        newPix.red = red.pixels[i].red;
        newPix.blue = blue.pixels[i].blue;
        newPix.green = green.pixels[i].green;

        nImg.pixels.push_back(newPix);
    }

    return nImg;
};

Image flip(Image& img) {
    Image nImg;

    nImg.header = img.header;

    for (int i = 0; i < img.pixels.size(); i++) {
        nImg.pixels.push_back(img.pixels[img.pixels.size() - i - 1]);
    }

    return nImg;
};

int main() {
    //header testing
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
    Image part1Img1 = ReadPic("input/layer1.tga");
    Image part1Img2 = ReadPic("input/pattern1.tga");

    Image part1Img = multiply(part1Img1, part1Img2);
    WritePic(part1Img, "output/part1.tga");

    //part 2.
    Image part2Img1 = ReadPic("input/car.tga");
    Image part2Img2 = ReadPic("input/layer2.tga");

    Image part2Img = subtract(part2Img1, part2Img2);
    WritePic(part2Img, "output/part2.tga");

    //part 3.
    Image part3Img1 = ReadPic("input/layer1.tga");
    Image part3Img2 = ReadPic("input/pattern2.tga");

    Image part3Img_1 = multiply(part3Img1, part3Img2);
    
    Image part3Img3 = ReadPic("input/text.tga");
    
    Image part3Img_2 = screen(part3Img_1,part3Img3);
    WritePic(part3Img_2, "output/part3.tga");

    //part 4.
    Image part4Img1 = ReadPic("input/layer2.tga");
    Image part4Img2 = ReadPic("input/circles.tga");

    Image part4Img_1 = multiply(part4Img1,part4Img2);

    Image part4Img3 = ReadPic("input/pattern2.tga");

    Image part4Img_2 = subtract(part4Img_1, part4Img3);
    WritePic(part4Img_2, "output/part4.tga");

    //part 5.
    Image part5Img1 = ReadPic("input/layer1.tga");
    Image part5Img2 = ReadPic("input/pattern1.tga");

    Image part5Img = overlay(part5Img1, part5Img2);
    WritePic(part5Img, "output/part5.tga");

    //part 6.
    Image part6img1 = ReadPic("input/car.tga");
    Image part6Img = add(part6img1, 200, "green");
    WritePic(part6Img, "output/part6.tga");

    //part 7.
    Image part7img1 = ReadPic("input/car.tga");
    Image part7Img = multiply(part7img1, 4, "red");
    Image part7Img_ = multiply(part7Img, 0, "blue");

    WritePic(part7Img_, "output/part7.tga");

    //part 8.
    Image part8img1 = ReadPic("input/car.tga");

    Image part8red = onlyColor(part8img1, "red");
    Image part8green = onlyColor(part8img1, "green");
    Image part8blue = onlyColor(part8img1, "blue");

    WritePic(part8blue, "output/part8_b.tga");
    WritePic(part8green, "output/part8_g.tga");
    WritePic(part8red, "output/part8_r.tga");

    //part 9.
    Image red = ReadPic("input/layer_red.tga");
    Image blue = ReadPic("input/layer_blue.tga");
    Image green = ReadPic("input/layer_green.tga");

    Image rgb = combine(red, green, blue);
    WritePic(rgb, "output/part9.tga");

    //part 10.
    Image Part10Img = ReadPic("input/text2.tga");

    Image flipee = flip(Part10Img);
    WritePic(flipee, "output/part10.tga");
};