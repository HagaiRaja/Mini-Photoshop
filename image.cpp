#include "image.h"
#include <QDebug>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
using namespace std;

Image::Image(char *filename)
{
    char *token = filename;
    while (*token != '.')
    {
        printf("%s\n", token);
        fflush(stdout);
        token = token + 1 * sizeof(*token);
    }
    token = token + 1 * sizeof(*token);
    const char *extension = token;
    if (!strcmp(extension, "bmp"))
    {
        // READ BMP

        int i;
        FILE *f = fopen(filename, "rb");
        unsigned char info[54];
        fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

        // extract image height and width from header
        w = *(int *)&info[18];
        h = *(int *)&info[22];

        uint16_t bitsPerPixel = *reinterpret_cast<uint16_t *>(&info[28]);
        uint32_t numColors = *reinterpret_cast<uint32_t *>(&info[46]);
        printf("%d\n", bitsPerPixel);
        printf("%d\n", numColors);
        fflush(stdout);
        uint colorTableSize = 4 * numColors;
        unsigned char *colorTable = new unsigned char[colorTableSize];
        if (bitsPerPixel <= 8)
        {
            fread(colorTable, sizeof(unsigned char), colorTableSize, f);
        }
        printf("color table: %s\n", colorTable);
        fflush(stdout);
        uint8_t colorPixelSize = 0;
        if (bitsPerPixel <= 8)
        {
            colorPixelSize = 1;
        }
        else
        {
            colorPixelSize = 3;
        }
        uint size = colorPixelSize * w * h;
        unsigned char *data = new unsigned char[size]; // allocate 3 bytes per pixel

        fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
                                                     //        printf("%s\n", data);
                                                     //        fflush(stdout);
        fclose(f);
        pixels = new Rgba[w * h];
        for (uint i = 0; i < h; i++)
        {
            for (uint j = 0; j < w; j++)
            {
                pixels[(i * w) + j] = Rgba(
                    data[colorPixelSize * (i * w + j) + 2],
                    data[colorPixelSize * (i * w + j) + 1],
                    data[colorPixelSize * (i * w + j) + 0],
                    0);
                printf("<%d,%d,%d>\n",
                       *(uint8_t *)data[colorPixelSize * (i * w + j) + 2],
                       *(uint8_t *)data[colorPixelSize * (i * w + j) + 1],
                       *(uint8_t *)data[colorPixelSize * (i * w + j) + 0]);
                fflush(stdout);
            }
        }
    }
    else if (!strcmp(extension, "ppm"))
    {
        FILE *f = fopen(filename, "rb");
        char *type = reinterpret_cast<char *>(malloc(2 * sizeof(char)));
        char *dimensions = reinterpret_cast<char *>(malloc(15 * sizeof(char)));
        char *maxLevelString = reinterpret_cast<char *>(malloc(4 * sizeof(char)));
        uint32_t maxLevel = 0;
        fgets(type, sizeof(type), f);
        printf("type = %s\n", type);

        fgets(dimensions, sizeof(dimensions), f);
        printf("dimensions = %s\n", dimensions);

        fgets(maxLevelString, sizeof(maxLevelString), f);
        printf("maxString = %s\n", maxLevelString);

        while (*maxLevelString == '\0' || *maxLevelString == '\n')
        {
            fgets(maxLevelString, sizeof(maxLevelString), f);
            printf("maxString = %s\n", maxLevelString);
        }
        fflush(stdout);
        w = uint(strtol(strtok(dimensions, " "), nullptr, 10));
        h = uint(strtol(strtok(nullptr, " "), nullptr, 10));
        maxLevel = uint(strtol(maxLevelString, nullptr, 10));
        printf("xMax = %d\n", w);
        printf("xMin = %d\n", h);

        printf("maxLevel = %d\n", maxLevel);
        fflush(stdout);

        uint size = 3 * w * h;
        unsigned char *data = new unsigned char[size];
        fread(data, sizeof(unsigned char), size, f);
        //        printf("data: %s\n", data);
        fclose(f);
        pixels = new Rgba[w * h];
        for (uint i = 0; i < h; i++)
        {
            for (uint j = 0; j < w; j++)
            {
                pixels[(i * w) + j] = Rgba(
                    data[3 * (i * w + j)],
                    data[3 * (i * w + j) + 1],
                    data[3 * (i * w + j) + 2],
                    0);
            }
        }
        //        fflush(stdout);
    }
    else if (!strcmp(extension, "pgm"))
    {
        // READ PGM
        char *type = new char[2];
        FILE *myfile = fopen(filename, "rb");

        fgets(type, sizeof(type), myfile);
        cout << type;
        if (!strcmp(type, "P5\n"))
        {
            char *dimension = new char[15];
            fgets(dimension, sizeof(dimension), myfile);
            int width = atoi(strtok(dimension, " "));
            int height = atoi(strtok(NULL, " "));
            cout << width << '\n';
            cout << height << '\n';

            char *grayscale_level_string = new char[3];
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
                    cout << int(data[i * width + j]) << " ";
                    pixels[i * width + j] = Rgba(data[i * width + j], data[i * width + j], data[i * width + j], 0);
                    fflush(stdout);
                }
                cout << endl;
            }
        }
        else if (!strcmp(type, "P2\n")) {
            char* dimension = new char[15];
            fgets(dimension, sizeof(dimension), myfile);
            int width = atoi(strtok(dimension, " "));
            int height = atoi(strtok(NULL, " "));

            char* grayscale_level_string = new char[3];
            fgets(grayscale_level_string, sizeof(grayscale_level_string), myfile);
            int grayscale_level = atoi(grayscale_level_string);

            grayscale_level_string = new char[3];
            fgets(grayscale_level_string, sizeof(grayscale_level_string), myfile);
            grayscale_level = atoi(grayscale_level_string);

            w = uint(width);
            h = uint(height);

            pixels = new Rgba[w * h];
            pixels_ori = new Rgba[w * h];
            int temp;
            for (int i = 0; i < height; ++i)
            {
                for (int j = 0; j < width; ++j)
                {
                    fscanf (myfile, "%d", &temp);
                    pixels[i*width + j] = Rgba(temp, temp, temp,0);
                    pixels_ori[i*width + j] = Rgba(temp, temp, temp,0);
                }
            }
        }
        else {
            cout << "Unable to open file";
        }
    }
    else cout << "Unable to open file";
}

QImage Image::getImage()
{
    QImage img(w, h, QImage::Format_RGBA8888);
    printf("w = %d, h = %d \n", w, h);
    fflush(stdout);
    img.fill(QColor(Qt::white).rgba());

    for (uint x = 0; x < h; ++x) {
        for (uint y = 0; y < w; ++y) {
            img.setPixel(y, x, qRgb(pixels[(x*w)+y].r, pixels[(x*w)+y].g, pixels[(x*w)+y].b));
        }
    }
    return img;
}

void Image::negatify() {
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i*w + j];
            pixels[i*w + j] = Rgba(255 - temp.r, 255 - temp.g, 255 - temp.b,0);
        }
    }
}

void Image::grayscale() {
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i*w + j];
            uint grayscale_value = uint(float(temp.r)*0.298 + float(temp.g)*0.586 + float(temp.b)* 0.143);
            pixels[i*w + j] = Rgba(grayscale_value, grayscale_value, grayscale_value,0);
        }
    }
}

void Image::flip_vertical() {
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w/2; ++j)
        {
            Rgba temp = pixels[i*w + j];
            pixels[i*w + j] = pixels[i*w + w - j];
            pixels[i*w + w - j] = temp;
        }
    }
}

void Image::flip_horizontal() {
    for (uint i = 0; i < h/2; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i*w + j];
            pixels[i*w + j] = pixels[(h-i)*w + j];
            pixels[(h-i)*w + j] = temp;
        }
    }
}

void Image::rotate_90_clockwise() {
    Rgba *pixel_result = new Rgba[w*h];
    //pixel_result ->
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            pixel_result[j*h+(h-1-i)] = pixels[i*w+j];
        }
    }
    pixels = pixel_result;
    uint temp = w;
    w = h;
    h = temp;
}

void Image::rotate_90_c_clockwise() {
    Rgba *pixel_result = new Rgba[w*h];
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            pixel_result[(w-1-j)*h+i] = pixels[i*w+j];
        }
    }
    pixels = pixel_result;
    uint temp = w;
    w = h;
    h = temp;
}

void Image::save(char *filename) {
    int i, j, temp = 0;
    int width = int(w), height = int(h);

    FILE* pgmimg;
    pgmimg = fopen(filename, "wb");

    // Writing Magic Number to the File
    fprintf(pgmimg, "P2\n");

    // Writing Width and Height
    fprintf(pgmimg, "%d %d\n", width, height);

    // Writing the maximum gray value
    fprintf(pgmimg, "255\n");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            Rgba temp = pixels[i*width + j];
            int grayscale_value = uint(float(temp.r)*0.298 + float(temp.g)*0.586 + float(temp.b)* 0.143);

            // Writing the gray values in the 2D array to the file
            fprintf(pgmimg, "%d ", grayscale_value);
        }
        fprintf(pgmimg, "\n");
    }
    fclose(pgmimg);
}


