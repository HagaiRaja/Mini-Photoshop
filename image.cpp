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
//    cout << type;
    if (!strcmp(type, "P5\n")) {
        char* dimension = new char[15];
        fgets(dimension, sizeof(dimension), myfile);
        int width = atoi(strtok(dimension, " "));
        int height = atoi(strtok(NULL, " "));
//        cout << width << '\n';
//        cout << height << '\n';

        char* grayscale_level_string = new char[3];
        fgets(grayscale_level_string, sizeof(grayscale_level_string), myfile);
        int grayscale_level = atoi(grayscale_level_string);

        grayscale_level_string = new char[3];
        fgets(grayscale_level_string, sizeof(grayscale_level_string), myfile);
        grayscale_level = atoi(grayscale_level_string);
//        cout << grayscale_level << endl;

        uint size = width * height;
        w = uint(width);
        h = uint(height);
        unsigned char *data = new unsigned char[size];
        fread(data, sizeof(unsigned char), size, myfile);

        pixels = new Rgba[w * h];
        pixels_ori = new Rgba[w * h];
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
//                cout << int(data[i*width + j]) << " ";
                pixels[i*width + j] = Rgba(data[i*width + j], data[i*width + j], data[i*width + j],0);
                pixels_ori[i*width + j] = Rgba(data[i*width + j], data[i*width + j], data[i*width + j],0);
//                fflush(stdout);
            }
//            cout << endl;
        }
    }
    else cout << "Unable to open file";
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

void Image::negatify() {
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i*w + j];
            pixels[i*w + j] = Rgba(255 - temp.r, 255 - temp.g, 255 - temp.b,0);
        }
    }
}
