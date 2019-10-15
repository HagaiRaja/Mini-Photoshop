#include "image.h"
#include <QDebug>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
using namespace std;

Image::Image(char* filename)
{
    // READ PGM
    char* type = new char[2];
    FILE* myfile = fopen(filename, "rb");

    fgets(type, sizeof(type), myfile);
    cout << type;
    if (!strcmp(type, "P5\n")) {
        char* dimension = new char[15];
        fgets(dimension, sizeof(dimension), myfile);
        int width = atoi(strtok(dimension, " "));
        int height = atoi(strtok(NULL, " "));
        cout << width << '\n';
        cout << height << '\n';

        char* grayscale_level_string = new char[3];
        fgets(grayscale_level_string, sizeof(grayscale_level_string), myfile);
        int grayscale_level = atoi(grayscale_level_string);

        grayscale_level_string = new char[3];
        fgets(grayscale_level_string, sizeof(grayscale_level_string), myfile);
        grayscale_level = atoi(grayscale_level_string);
        cout << grayscale_level << endl;

        uint size = width * height;
        w = uint(width);
        h = uint(height);
        unsigned char *data = new unsigned char[size];
        fread(data, sizeof(unsigned char), size, myfile);

        pixels = new Rgba[w * h];
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                cout << int(data[i*width + j]) << " ";
                pixels[i*width + j] = Rgba(data[i*width + j], data[i*width + j], data[i*width + j],0);
                fflush(stdout);
            }
            cout << endl;
        }
    }
    else cout << "Unable to open file";

    // READ PPM
//    ifstream fp(filename);
//    if (fp.fail())
//        return; //You failed

//    //Read the Magic Number
//    string mg_num, width_str, height_str, range_str;
//    fp >> mg_num;

//    if (mg_num != "P3") {
//        fp.close();
//        return; //The file is not a ASCII PPM file!
//    }

//    fp >> width_str >> height_str >> range_str;
//    w = atoi(width_str .c_str()); //Takes the number string and converts it to an integer
//    h = atoi(height_str.c_str());

//    //Read the values into the vector directly.
//    string _R, _G, _B;
//    for (unsigned int i = 0; i < w * h; i++) {
//        fp >> _R >> _G >> _B;
//        pixels[i] = Rgba(atoi(_R.c_str()),atoi(_G.c_str()),atoi(_B.c_str()),0);
//        qInfo() << pixels[i].r << " " << pixels[i].g << " " << pixels[i].b;
//    }

//    fp.close();

    // READ BMP

//    int i;
//    FILE* f = fopen(filename, "rb");
//    unsigned char info[54];
//    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

//    // extract image height and width from header
//    w = *(int*)&info[18];
//    h = *(int*)&info[22];

//    int size = 3 * w * h;
//    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
//    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
//    fclose(f);
//    pixels = new Rgba[w * h];

//    for(i = 0; i < size; i += 3)
//    {
//        unsigned char tmp = data[i];
//        data[i] = data[i+2];
//        data[i+2] = tmp;

//        if (data[i] != 0) {
//            qInfo() << data[i] << " " << data[i+1] << " " << data[i+2];
//        }
//    }

//    for(int i = 0; i < h; i++)
//    {
//        for(int j = 0; j < w; j++)
//        {
//            if (i < 200 && j < 300) {
//                pixels[(i*w)+j] = Rgba(255,0,0,0);
//            }
//            else {
//                pixels[(i*w)+j] = Rgba(
//                            data[3 * (i  * w + j)],
//                            data[3 * (i * w + j) + 1],
//                            data[3 * (i * w + j) + 2],
//                            0);

//            }
//            pixels[(i*w)+j] = Rgba(
//                        data[3 * (i * w + j)],
//                        data[3 * (i * w + j) + 1],
//                        data[3 * (i * w + j) + 2],
//                        0);
//        }
//    }

    // READ PBM
    char* type = new char[2];
    FILE* pbmFile = fopen(filename, "rb");

    if (!strcmp(type, "P1\n")) {
        char* dimension = new char [15];
        fgets(dimension, sizeof(dimension), pbmFile);
        int width = atoi(strtok(dimension, " "));
        int height = atoi(strtok(NULL, " "));
        cout << width << '\n';
        cout << height << '\n';

        uint size = width * height;
        w = uint(width);
        h = uint(height);
        unsigned char *data = new unsigned char[size];
        fread(data, sizeof(unsigned char), size, pbmFile);

        pixels = new Rgba[w * h];
        int temp;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                temp = int(data[i*width + j]);
                cout << temp << " ";
                if (temp != 0) {
                    pixels[i*width + j] = Rgba(255, 255, 255, 0);
                }
                else {
                    pixels[i*width + g] = Rgba(0, 0, 0, 0);
                }
                fflush(stdout);
            }
            cout << endl;
        }
    }

}

QImage Image::getImage() {
    QImage img(w, h, QImage::Format_RGBA8888);
    img.fill(QColor(Qt::white).rgba());

    for (int x = 0; x < h; ++x) {
        for (int y = 0; y < w; ++y) {
//            if (x < 200 && y < 300) {
//                img.setPixel(x, y, qRgb(0,255,0));
//            }
//            else {
//                img.setPixel(x, y, qRgb(pixels[(x*4)+y].r, pixels[(x*4)+y].g, pixels[(x*4)+y].b));

//            }
            img.setPixel(y, x, qRgb(pixels[(x*w)+y].r, pixels[(x*w)+y].g, pixels[(x*w)+y].b));
//            img.setPixel(x, y, qRgb(255,0,0));
        }
    }
    return img;
}
