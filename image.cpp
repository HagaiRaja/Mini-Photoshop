#include "image.h"
#include<QDebug>

Image::Image(char* filename)
{
    // READ BMP

    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    w = *(int*)&info[18];
    h = *(int*)&info[22];

    int size = 3 * w * h;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);
    pixels = new Rgba[w * h];

    for(i = 0; i < size; i += 3)
    {
        unsigned char tmp = data[i];
        data[i] = data[i+2];
        data[i+2] = tmp;

        if (data[i] != 0) {
            qInfo() << data[i] << " " << data[i+1] << " " << data[i+2];
        }
    }

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
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
            pixels[(i*w)+j] = Rgba(
                        data[3 * (i * w + j)],
                        data[3 * (i * w + j) + 1],
                        data[3 * (i * w + j) + 2],
                        0);
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
            img.setPixel(x, y, qRgb(pixels[(x*w)+y].r, pixels[(x*w)+y].g, pixels[(x*w)+y].b));
//            img.setPixel(x, y, qRgb(255,0,0));
        }
    }
    return img;
}
