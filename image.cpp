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
    // READ PGM
    char *type = new char[2];
    FILE *myfile = fopen(filename, "rb");

    fgets(type, sizeof(type), myfile);
    //    cout << type;
    if (!strcmp(type, "P5\n"))
    {
        char *dimension = new char[15];
        fgets(dimension, sizeof(dimension), myfile);
        int width = atoi(strtok(dimension, " "));
        int height = atoi(strtok(NULL, " "));
        //        cout << width << '\n';
        //        cout << height << '\n';

        char *grayscale_level_string = new char[3];
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
                uint temp = uint(float(data[i * width + j]) / float(grayscale_level) * float(255));
                pixels[i * width + j] = Rgba(temp, temp, temp, 0);
                pixels_ori[i * width + j] = Rgba(temp, temp, temp, 0);
                //                fflush(stdout);
            }
            //            cout << endl;
        }
    }
    else if (!strcmp(type, "P2\n"))
    {
        char *dimension = new char[15];
        fgets(dimension, sizeof(dimension), myfile);
        int width = atoi(strtok(dimension, " "));
        int height = atoi(strtok(NULL, " "));

        char *grayscale_level_string = new char[3];
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
                fscanf(myfile, "%d", &temp);
                pixels[i * width + j] = Rgba(temp, temp, temp, 0);
                pixels_ori[i * width + j] = Rgba(temp, temp, temp, 0);
            }
        }
    }
    else
        cout << "Unable to open file";
}

QImage Image::getImage()
{
    QImage img(w, h, QImage::Format_RGBA8888);
    img.fill(QColor(Qt::white).rgba());

    for (uint x = 0; x < h; ++x)
    {
        for (uint y = 0; y < w; ++y)
        {
            img.setPixel(y, x, qRgb(pixels[(x * w) + y].r, pixels[(x * w) + y].g, pixels[(x * w) + y].b));
        }
    }
    return img;
}

void Image::negatify()
{
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i * w + j];
            pixels[i * w + j] = Rgba(255 - temp.r, 255 - temp.g, 255 - temp.b, 0);
        }
    }
}

void Image::save(char *filename)
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
    }
    else if (!strcmp(extension, "ppm"))
    {
        FILE *ppmimg;
        ppmimg = fopen(filename, "wb");

        // Writing Magic Number to the File
        fprintf(ppmimg, "P6\n");

        // Writing Width and Height
        fprintf(ppmimg, "%d %d\n", w, h);

        // Writing the maximum gray value
        fprintf(ppmimg, "255\n");
        for (uint i = 0; i < h; i++)
        {
            for (uint j = 0; j < w; j++)
            {
                fprintf(ppmimg, "%c%c%c", pixels[i * w + j].r, pixels[i * w + j].g, pixels[i * w + j].b);
            }
        }
        fclose(ppmimg);
    }
    else if (!strcmp(extension, "pgm"))
    {
        int i, j, temp = 0;
        int width = int(w), height = int(h);
        FILE *pgmimg;
        pgmimg = fopen(filename, "wb");

        // Writing Magic Number to the File
        fprintf(pgmimg, "P2\n");

        // Writing Width and Height
        fprintf(pgmimg, "%d %d\n", width, height);

        // Writing the maximum gray value
        fprintf(pgmimg, "255\n");
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
            {
                temp = pixels[i * width + j].r;

                // Writing the gray values in the 2D array to the file
                fprintf(pgmimg, "%d ", temp);
            }
            fprintf(pgmimg, "\n");
        }
        fclose(pgmimg);
    }
}
