#include "image.h"
#include <QDebug>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <cmath>
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
        fclose(f);
        pixels = new Rgba[w * h];
        pixels_ori = new Rgba[w * h];
        for (uint i = 0; i < h; i++)
        {
            for (uint j = 0; j < w; j++)
            {
                pixels[(i * w) + j] = Rgba(
                    data[colorPixelSize * (i * w + j) + 2],
                    data[colorPixelSize * (i * w + j) + 1],
                    data[colorPixelSize * (i * w + j) + 0],
                    0);
                pixels_ori[(i * w) + j] = Rgba(
                    data[colorPixelSize * (i * w + j) + 2],
                    data[colorPixelSize * (i * w + j) + 1],
                    data[colorPixelSize * (i * w + j) + 0],
                    0);
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
        printf("yMax = %d\n", h);

        printf("maxLevel = %d\n", maxLevel);
        fflush(stdout);

        uint size = 3 * w * h;
        pixels = new Rgba[w * h];
        pixels_ori = new Rgba[w*h];
        if (!strcmp(type, "P3\r\n") || !strcmp(type, "P3\n"))
        {
            uint8_t *data = new uint8_t[size];
            for (uint i = 0; i < h; i++)
            {
                for (uint j = 0; j < 3 * w; j++)
                {
                    int temp;
                    fscanf(f, "%d", &temp);
                    data[i * w * 3 + j] = static_cast<uint8_t>((temp / static_cast<float>(maxLevel)) * 255);
                    printf("[%d] %hhu\n", i * w * 3 + j, data[i * w * 3 + j]);
                    fflush(stdout);
                }
            }
            for (uint i = 0; i < h; i++)
            {
                for (uint j = 0; j < w; j++)
                {
                    pixels[(i * w) + j] = Rgba(
                        data[3 * (i * w + j)],
                        data[3 * (i * w + j) + 1],
                        data[3 * (i * w + j) + 2],
                        0);
                    pixels_ori[(i * w) + j] = Rgba(
                        data[3 * (i * w + j)],
                        data[3 * (i * w + j) + 1],
                        data[3 * (i * w + j) + 2],
                        0);
                }
            }
        }
        else
        { // P6
            unsigned char *data = new unsigned char[size];
            fread(data, sizeof(unsigned char), size, f);
            fclose(f);
            for (uint i = 0; i < h; i++)
            {
                for (uint j = 0; j < w; j++)
                {
                    pixels[(i * w) + j] = Rgba(
                        static_cast<unsigned char>((data[3 * (i * w + j)] / static_cast<float>(maxLevel)) * 255),
                        static_cast<unsigned char>((data[3 * (i * w + j) + 1] / static_cast<float>(maxLevel)) * 255),
                        static_cast<unsigned char>((data[3 * (i * w + j) + 2] / static_cast<float>(maxLevel)) * 255),
                        0);
                    pixels_ori[(i * w) + j] = Rgba(
                        static_cast<unsigned char>((data[3 * (i * w + j)] / static_cast<float>(maxLevel)) * 255),
                        static_cast<unsigned char>((data[3 * (i * w + j) + 1] / static_cast<float>(maxLevel)) * 255),
                        static_cast<unsigned char>((data[3 * (i * w + j) + 2] / static_cast<float>(maxLevel)) * 255),
                        0);
                }
            }
        }
    }
    else if (!strcmp(extension, "pgm"))
    {
        // READ PGM
        char *type = new char[2];
        FILE *myfile = fopen(filename, "rb");

        fgets(type, sizeof(type), myfile);
        cout << type;

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
        uint size = width * height;
        pixels = new Rgba[w * h];
        pixels_ori = new Rgba[w * h];

        if (!strcmp(type, "P5\n"))
        {
            unsigned char *data = new unsigned char[size];
            fread(data, sizeof(unsigned char), size, myfile);

            for (int i = 0; i < height; ++i)
            {
                for (int j = 0; j < width; ++j)
                {
                    cout << int(data[i * width + j]) << " ";
                    uint color = uint(double(data[i * width + j]) / double(grayscale_level) * 255);
                    pixels[i * width + j] = Rgba(color, color, color, 0);
                    pixels_ori[i * width + j] = Rgba(color, color, color, 0);
                    fflush(stdout);
                }
                cout << endl;
            }
        }
        else if (!strcmp(type, "P2\n"))
        {
            int temp;
            for (int i = 0; i < height; ++i)
            {
                for (int j = 0; j < width; ++j)
                {
                    fscanf(myfile, "%d", &temp);
                    uint color = uint(double(temp) / double(grayscale_level) * 255);
                    pixels[i * width + j] = Rgba(color, color, color, 0);
                    pixels_ori[i * width + j] = Rgba(color, color, color, 0);
                }
            }
        }
        else
        {
            cout << "Unable to open file";
        }
    }
    else
        cout << "Unable to open file";
}

QImage Image::getImage()
{
    QImage img(w, h, QImage::Format_RGBA8888);
    printf("w = %d, h = %d \n", w, h);
    fflush(stdout);
    img.fill(QColor(Qt::white).rgba());

    for (uint y = 0; y < h; ++y)
    {
        for (uint x = 0; x < w; ++x)
        {
            img.setPixel(x, y, qRgb(pixels[(y * w) + x].r, pixels[(y * w) + x].g, pixels[(y * w) + x].b));
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

void Image::grayscale()
{
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i * w + j];
            uint grayscale_value = uint(float(temp.r) * 0.298 + float(temp.g) * 0.586 + float(temp.b) * 0.143);
            pixels[i * w + j] = Rgba(grayscale_value, grayscale_value, grayscale_value, 0);
        }
    }
}

void Image::flip_vertical()
{
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w / 2; ++j)
        {
            Rgba temp = pixels[i * w + j];
            pixels[i * w + j] = pixels[i * w + w - j];
            pixels[i * w + w - j] = temp;
        }
    }
}

void Image::flip_horizontal()
{
    for (uint i = 0; i < h / 2; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i * w + j];
            pixels[i * w + j] = pixels[(h - i) * w + j];
            pixels[(h - i) * w + j] = temp;
        }
    }
}

void Image::rotate_90_clockwise()
{
    Rgba *pixel_result = new Rgba[w * h];
    //pixel_result ->
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            pixel_result[j * h + (h - 1 - i)] = pixels[i * w + j];
        }
    }
    pixels = pixel_result;
    uint temp = w;
    w = h;
    h = temp;
}

void Image::rotate_90_c_clockwise()
{
    Rgba *pixel_result = new Rgba[w * h];
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            pixel_result[(w - 1 - j) * h + i] = pixels[i * w + j];
        }
    }
    pixels = pixel_result;
    uint temp = w;
    w = h;
    h = temp;
}

void Image::change_brightness(int value) {
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i*w+j];
            int newR, newG, newB;
            // Add value to R
            newR = int(temp.r)+value;
            if (newR > 255) {
                newR = 255;
            }
            else if (newR < 0) {
                newR = 0;
            }
            // Add value to G
            newG = int(temp.g)+value;
            if (newG > 255) {
                newG = 255;
            }
            else if(newG < 0) {
                newG = 0;
            }
            // Add value to B
            newB = int(temp.b)+value;
            if (newB > 255) {
                newB = 255;
            }
            else if (newB < 0) {
                newB = 0;
            }

            pixels[i*w+j] = Rgba (uint(newR), uint(newG), uint(newB), 0);
        }
    }
}

void Image::operation_bool(Image *secondImage, bool OR)
{
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i * w + j];
            Rgba temp_second;
            (OR) ? temp_second = Rgba(0, 0, 0, 0) : temp_second = Rgba(255, 255, 255, 0);

            if (i < secondImage->h && j < secondImage->w)
            {
                temp_second = secondImage->pixels[i * w + j];
            }
            Rgba bool_result;
            if (OR)
            {
                bool_result = Rgba(
                    temp.r | temp_second.r,
                    temp.g | temp_second.g,
                    temp.b | temp_second.b,
                    temp.a | temp_second.a);
            }
            else
            {
                bool_result = Rgba(
                    temp.r & temp_second.r,
                    temp.g & temp_second.g,
                    temp.b & temp_second.b,
                    temp.a & temp_second.a);
            }
            pixels[i * w + j] = bool_result;
        }
    }
}

void Image::operation_not()
{
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i * w + j];
            Rgba not_result = Rgba(~temp.r, ~temp.g, ~temp.b, temp.a);
            pixels[i * w + j] = not_result;
        }
    }
}

void Image::update_translate(bool from_ori)
{
    Rgba *pixel_result = new Rgba[w * h];
    //pixel_result ->
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            if (int(i) - int(translate_y) >= 0 && int(i) - int(translate_y) < int(h) && int(j) - int(translate_x) >= 0 && int(j) - int(translate_x) < int(w))
            {
                if (from_ori)
                {
                    pixel_result[i * w + j] = pixels_ori[(i - translate_y) * w + j - translate_x];
                }
                else
                {
                    pixel_result[i * w + j] = pixels[(i - translate_y) * w + j - translate_x];
                }
            }
            else
            {
                pixel_result[i * w + j] = Rgba(0, 0, 0, 0);
            }
        }
    }
    pixels = pixel_result;
}

void Image::operation_arithmetic(Image *secondImage)
{
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i * w + j];
            Rgba temp_second(0, 0, 0, 0);

            if (i < secondImage->h && j < secondImage->w)
            {
                temp_second = secondImage->pixels[i * w + j];
            }

            Rgba bool_result = Rgba(
                (temp.r + temp_second.r) > 255 ? 255 : (temp.r + temp_second.r),
                (temp.r + temp_second.g) > 255 ? 255 : (temp.g + temp_second.g),
                (temp.r + temp_second.b) > 255 ? 255 : (temp.b + temp_second.b),
                (temp.r + temp_second.a) > 255 ? 255 : (temp.a + temp_second.a));
            pixels[i * w + j] = bool_result;
        }
    }
}

void Image::transform_gamma(double gamma, int constant) {
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i * w + j];
            double r = constant * (pow(temp.r, gamma)),
                    g = constant * (pow(temp.g, gamma)),
                    b = constant * (pow(temp.b, gamma)),
                    a = constant * (pow(temp.a, gamma));

            if (r > 255) r = 255; if (r < 0) r = 0;
            if (g > 255) g = 255; if (g < 0) g = 0;
            if (b > 255) b = 255; if (b < 0) b = 0;
            if (a > 255) a = 255; if (a < 0) a = 0;

            pixels[i * w + j] = Rgba(uint(r), uint(g), uint(b), uint(a));
//            cout << r << " " << g << " " << b << " " << a << endl;
//            fflush(stdout);
        }
    }
//    cout << gamma << " " << constant << endl;
}

void Image::log_transform(const double constant, const bool inverse) {
    for(uint i = 0 ; i < h ; i++){
        for(uint j = 0 ; j < w ; j++) {
            int logR;
            int logG;
            int logB;
            if(!inverse) {
                logR = static_cast<int>(constant * log(1+pixels[i*w+j].r));
                logG = static_cast<int>(constant * log(1+pixels[i*w+j].g));
                logB = static_cast<int>(constant * log(1+pixels[i*w+j].b));
            } else {
                logR = static_cast<int>(pow(10,pixels[i*w+j].r/constant)-1);
                logG = static_cast<int>(pow(10,pixels[i*w+j].g/constant)-1);
                logB = static_cast<int>(pow(10,pixels[i*w+j].b/constant)-1);
            }

            logR = (logR > 255)? 255 : logR;
            logR = (logR < 0)? 0 : logR;
            logG = (logG > 255)? 255 : logG;
            logG = (logG < 0)? 0 : logG;
            logB = (logB > 255)? 255 : logB;
            logB = (logB < 0)? 0 : logB;
            pixels[i * w + j] = Rgba(static_cast<uint8_t>(logR), static_cast<uint8_t>(logG), static_cast<uint8_t>(logB), 0);
        }
    }
}

void Image::graylevel_slicing(int start, int end, bool preserve) {
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i * w + j];
            int grayscale_value = int(float(temp.r) * 0.298 + float(temp.g) * 0.586 + float(temp.b) * 0.143);

            if (grayscale_value >= start && grayscale_value <= end) {
                pixels[i * w + j] = Rgba(255,255,255,0);
            }
            else {
                if (!preserve) {
                    pixels[i * w + j] = Rgba(0,0,0,0);
                }
            }
        }
    }
}


void Image::bit_slicing(uint kernel) {
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i * w + j];
            uint grayscale_value = uint(float(temp.r) * 0.298 + float(temp.g) * 0.586 + float(temp.b) * 0.143);
            if ((grayscale_value & kernel) != 0) {
                pixels[i * w + j] = Rgba(255,255,255,0);
            }
            else {
                pixels[i * w + j] = Rgba(0,0,0,0);
            }
        }
    }
}

void Image::reset() {
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            pixels[i * w + j] = pixels_ori[i * w + j];
        }
    }
}

void Image::zoom(int percentage) {
    Rgba *pixel_result = new Rgba[w * h];
    uint x,y;
    double calc_x, calc_y, width = double(w), height = double(h);
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            calc_x = (width/2) - (((width/2) - double(j))/percentage * 100);
            calc_y = (height/2) - (((height/2) - double(i))/percentage * 100);

            x = uint(calc_x);
            y = uint(calc_y);
            if (x < 0 || x >= w || y < 0 || y >= h) {
                pixel_result[i * w + j] = Rgba(0,0,0,0);
            }
            else {
                pixel_result[i * w + j] = pixels[y * w + x];
            }
        }
    }
    pixels = pixel_result;
}

void Image::contrast_stretching(int x1, int y1, int x2, int y2) {
    uint transform_table[256];
    double calc;
    uint temp;

    // making table
    for (int i = 0; i < 256; i++) {
        if (i < x1) {
            calc = (double(y1)) / (double(x1)) * double(i);
        }
        else if (i >= x1 && i < x2) {
            calc = ((((double) (y1 - y2)) / ((double) (x1 - x2))) * i) +
                    double(y1) - ((((double) (y1 - y2)) / ((double) (x1 - x2))) * x1);
        }
        else {
            calc = ((((double) (255 - y2)) / ((double) (255 - x2))) * i) +
                    double(255) - ((((double) (255 - y2)) / ((double) (255 - x2))) * 255);
        }
        temp = (uint) calc;
        if (temp < 0) temp = 0;
        if (temp > 255) temp = 255;
        transform_table[i] = temp;
        cout << i << " " << temp << endl;
        fflush(stdout);
    }

    // updating rgb
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i * w + j];
            pixels[i * w + j] = Rgba(
                        transform_table[(int) temp.r],
                        transform_table[(int) temp.g],
                        transform_table[(int) temp.b],
                        temp.a
                    );
        }
    }
}

void Image::konvolusi(double kernel[], int dimension, double divident) {
    Rgba *pixel_result = new Rgba[w * h];
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            pixel_result[i * w + j] = pixels[i * w + j];
        }
    }

    int half = dimension/2;
    for (uint i = (dimension/2); i < h - (dimension/2); ++i)
    {
        for (uint j = (dimension/2); j < w - (dimension/2); ++j)
        {
            double r = 0, g = 0, b = 0;
            for (int k = -half; k <= half; k++) {
                for (int l = -half; l <= half; l++) {
                    r += double(pixels[((i+k) * w) + (j + l)].r) * kernel[(k+half)*dimension + l + half];
                    g += double(pixels[((i+k) * w) + (j + l)].g) * kernel[(k+half)*dimension + l + half];
                    b += double(pixels[((i+k) * w) + (j + l)].b) * kernel[(k+half)*dimension + l + half];
                }
            }
            if (divident > 0) {
                r /= divident;
                g /= divident;
                b /= divident;
            }
            if (r < 0) r = 0; if (r > 255) r = 255;
            if (g < 0) g = 0; if (g > 255) g = 255;
            if (b < 0) b = 0; if (b > 255) b = 255;
            pixel_result[i * w + j] = Rgba(uint(int(r)), uint(int(g)), uint(int(b)), 0);
        }
    }

    pixels = pixel_result;
}

void Image::cross_convolution(double kernel_x[], double kernel_y[], int dimension) {
    Rgba *pixel_result = new Rgba[w * h];
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            pixel_result[i * w + j] = pixels[i * w + j];
        }
    }

    int half = dimension/2;
    for (uint i = (dimension/2); i < h - (dimension/2); ++i)
    {
        for (uint j = (dimension/2); j < w - (dimension/2); ++j)
        {
            double r_x = 0, g_x = 0, b_x = 0;
            double r_y = 0, g_y = 0, b_y = 0;
            for (int k = -half; k <= half; k++) {
                for (int l = -half; l <= half; l++) {
                    r_x += double(pixels[((i+k) * w) + (j + l)].r) * kernel_x[(k+half)*dimension + l + half];
                    g_x += double(pixels[((i+k) * w) + (j + l)].g) * kernel_x[(k+half)*dimension + l + half];
                    b_x += double(pixels[((i+k) * w) + (j + l)].b) * kernel_x[(k+half)*dimension + l + half];
                    r_y += double(pixels[((i+k) * w) + (j + l)].r) * kernel_y[(k+half)*dimension + l + half];
                    g_y += double(pixels[((i+k) * w) + (j + l)].g) * kernel_y[(k+half)*dimension + l + half];
                    b_y += double(pixels[((i+k) * w) + (j + l)].b) * kernel_y[(k+half)*dimension + l + half];
                }
            }

            uint r = uint(int(pow( (pow(r_x, 2) + pow(r_y, 2)) ,0.5)) ); if (r > 255) r = 255;
            uint g = uint(int(pow( (pow(g_x, 2) + pow(g_y, 2)) ,0.5)) ); if (g > 255) g = 255;
            uint b = uint(int(pow( (pow(b_x, 2) + pow(b_y, 2)) ,0.5)) ); if (b > 255) b = 255;
            pixel_result[i * w + j] = Rgba(r, g, b, 0);
        }
    }

    pixels = pixel_result;
}

void Image::roberts() {
    Rgba *pixel_result = new Rgba[w * h], xy, x1y, xy1, x1y1;
    int r_plus_r, r_minus_r, r_plus_g, r_minus_g, r_plus_b, r_minus_b;
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            if (i  == h - 1 || j == w - 1) {
                pixel_result[i * w + j] = pixels[i * w + j];
            }
            else {
                xy = pixels[(i * w) + j];
                x1y = pixels[((i+1) * w) + j];
                xy1 = pixels[(i * w) + j + 1];
                x1y1 = pixels[((i+1) * w) + j + 1];
                r_plus_r = int(x1y1.r) - int(xy.r); if (r_plus_r < 0) r_plus_r *= -1;
                r_plus_g = int(x1y1.g) - int(xy.g); if (r_plus_g < 0) r_plus_g *= -1;
                r_plus_b = int(x1y1.b) - int(xy.b); if (r_plus_b < 0) r_plus_b *= -1;
                r_minus_r = int(xy1.r) - int(x1y.r); if (r_minus_r < 0) r_minus_r *= -1;
                r_minus_g = int(xy1.g) - int(x1y.g); if (r_minus_g < 0) r_minus_g *= -1;
                r_minus_b = int(xy1.b) - int(x1y.b); if (r_minus_b < 0) r_minus_b *= -1;
//                cout << r_plus_r << " " << r_plus_g << " " << r_plus_b <<
//                        " " << r_minus_r << " " << r_minus_g << " " << r_minus_b << endl;
//                fflush(stdout);

                pixel_result[i * w + j] = Rgba(
                            uint(r_plus_r + r_minus_r),
                            uint(r_plus_g + r_minus_g),
                            uint(r_plus_b + r_minus_b),
                            0);
            }
        }
    }
    pixels = pixel_result;
}

void Image::setFixedSize() {
    uint new_h = 200, new_w = 700;

    Rgba *pixel_result = new Rgba[new_w * new_h];
    uint x,y;
    double calc_x, calc_y, width = double(w), height = double(h);
    for (uint i = 0; i < new_h; ++i)
    {
        for (uint j = 0; j < new_w; ++j)
        {
            calc_x = double(j)/double(new_w) * width;
            calc_y = double(i)/double(new_h) * height;

            x = uint(calc_x);
            y = uint(calc_y);
            pixel_result[i * new_w + j] = pixels[y * w + x];
        }
    }
    pixels = pixel_result;
    w = new_w;
    h = new_h;
}

void Image::getPlateNumber() {
    double kernel[] = {
        1, 2, 1,
        2, 4, 2,
        1, 2, 1
    };

    double highPass[] = {
        -1, -1, -1,
        -1, 9, -1,
        -1, -1, -1
    };

//    this->konvolusi(kernel, 3, 16);
//    this->konvolusi(highPass, 3, 0);

    // bigger size
   this->setFixedSize();

    // filter by median
//    this->medianFilter();
}

void Image::medianFilter() {
    Rgba *pixel_result = new Rgba[w * h];
    Rgba temp;
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            temp = pixels[i * w + j];
            if (temp.r + temp.g + temp.b > 300) {
                pixel_result[i * w + j] = Rgba(255,255,255,0);
            }
            else {
                pixel_result[i * w + j] = Rgba(0,0,0,0);
            }
        }
    }

    pixels = pixel_result;
}

void Image::to_biner(int threshold) {
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            Rgba temp = pixels[i * w + j];
            int grayscale_value = uint(float(temp.r) * 0.298 + float(temp.g) * 0.586 + float(temp.b) * 0.143);
            if (grayscale_value > threshold) {
                pixels[i * w + j] = Rgba(255, 255, 255, 0);
            }
            else {
                pixels[i * w + j] = Rgba(0, 0, 0, 0);
            }
        }
    }
}

void Image::gradient() {
    Rgba *pixel_result = new Rgba[w * h], xy, x1y, xy1;
    double r_plus_r, r_minus_r, r_plus_g, r_minus_g, r_plus_b, r_minus_b;
    for (uint i = 0; i < h; ++i)
    {
        for (uint j = 0; j < w; ++j)
        {
            if (i  == h - 1 || j == w - 1) {
                pixel_result[i * w + j] = pixels[i * w + j];
            }
            else {
                xy = pixels[(i * w) + j];
                x1y = pixels[((i+1) * w) + j];
                xy1 = pixels[(i * w) + j + 1];
                r_plus_r = double(x1y.r) - double(xy.r); if (r_plus_r < 0) r_plus_r *= -1;
                r_plus_g = double(x1y.g) - double(xy.g); if (r_plus_g < 0) r_plus_g *= -1;
                r_plus_b = double(x1y.b) - double(xy.b); if (r_plus_b < 0) r_plus_b *= -1;
                r_minus_r = double(xy1.r) - double(xy.r); if (r_minus_r < 0) r_minus_r *= -1;
                r_minus_g = double(xy1.g) - double(xy.g); if (r_minus_g < 0) r_minus_g *= -1;
                r_minus_b = double(xy1.b) - double(xy.b); if (r_minus_b < 0) r_minus_b *= -1;

                uint r = uint(int(pow( (pow(r_plus_r, 2) + pow(r_minus_r, 2)) ,0.5)) ); if (r > 255) r = 255;
                uint g = uint(int(pow( (pow(r_plus_g, 2) + pow(r_minus_g, 2)) ,0.5)) ); if (g > 255) g = 255;
                uint b = uint(int(pow( (pow(r_plus_b, 2) + pow(r_minus_b, 2)) ,0.5)) ); if (b > 255) b = 255;
                pixel_result[i * w + j] = Rgba(r, g, b, 0);
            }
        }
    }
    pixels = pixel_result;
}

void Image::defineImageType(uint &type) {
    bool isBiner = true;
    bool isGrayscale = true;

    for (uint i = 0; i < h; ++i) {
        for (uint j = 0; j < w; ++j) {
            Rgba temp = pixels[i*w + j];
          if (isBiner) {
              isBiner = ((temp.r == 0 || temp.r == 255) && (temp.g == 0 || temp.g == 255) && (temp.b == 0 || temp.b == 255));
          }
          if (isGrayscale) {
              isGrayscale = ((temp.r == temp.g) && (temp.r == temp.b) && (temp.g == temp.b));
          }
        }
    }

    if (isBiner) {
        type = 0;
    }
    else if (isGrayscale) {
        type = 1;
    }
    else {
        type = 2;
    }
}

void Image::createHistogram(uint (&highestCountP) [3], uint (&cGrayLevel) [3], uint type, uint (&pixelCount) [3][256]) {
    for (uint i = 0; i < 3; i++) {
        cGrayLevel[i] = 0;
        highestCountP[i] = 0;

        for (uint j = 0; j < 256; j++) {
            pixelCount[i][j] = 0;
        }
    }

    for (uint i = 0; i < h; i++) {
        for (uint j = 0; j < w; j++) {
            Rgba temp = pixels[(i*w) + j];
            // Counting each graylevels

            pixelCount[0][uint(temp.r)]++;
            pixelCount[1][uint(temp.g)]++;
            pixelCount[2][uint(temp.b)]++;

            // Finding highest Pixel Count
            if (uint(temp.r) > cGrayLevel[0]) {
                cGrayLevel[0] = uint(temp.r);
            }
            if (uint(temp.g) > cGrayLevel[1]) {
                cGrayLevel[1] = uint(temp.g);
            }
            if (uint(temp.b) > cGrayLevel[2]) {
                cGrayLevel[2] = uint(temp.b);
            }
        }
    }

    for (uint i = 0; i < 256; i++) {
        if (pixelCount[0][i] > highestCountP[0]) {
            highestCountP[0] = pixelCount[0][i];
        }
        if (pixelCount[1][i] > highestCountP[1]) {
            highestCountP[1] = pixelCount[1][i];
        }
        if (pixelCount[2][i] > highestCountP[2]) {
            highestCountP[2] = pixelCount[2][i];
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
        int i, j;
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
                Rgba temp = pixels[i * width + j];
                int grayscale_value = uint(float(temp.r) * 0.298 + float(temp.g) * 0.586 + float(temp.b) * 0.143);

                // Writing the gray values in the 2D array to the file
                fprintf(pgmimg, "%d ", grayscale_value);
            }
            fprintf(pgmimg, "\n");
        }
        fclose(pgmimg);
    }
}

