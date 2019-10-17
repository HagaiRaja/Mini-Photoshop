#ifndef IMAGE_H
#define IMAGE_H

#define NULL 0
#include <QImage>

class Image
{
public:
    // Rgba structure, i.e. a pixel
    struct Rgba
    {
        Rgba() : r(0), g(0), b(0), a(0) {}
        Rgba(unsigned char c) : r(c), g(c), b(c), a(0) {}
        Rgba(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) : r(_r), g(_g), b(_b), a(_a) {}
        bool operator != (const Rgba &c) const
        { return c.r != r || c.g != g || c.b != b || c.a != a; }
        Rgba& operator *= (const Rgba &rgba)
        { r *= rgba.r, g *= rgba.g, b *= rgba.b; return *this; }
        Rgba& operator += (const Rgba &rgba)
        { r += rgba.r, g += rgba.g, b += rgba.b; return *this; }
        Rgba& operator -= (const Rgba &rgba)
        { r -= rgba.r, g -= rgba.g, b -= rgba.b; return *this; }
        unsigned char r, g, b, a;
    };

    Image() : w(0), h(0), pixels(nullptr) { /* empty image */ }

    Image(const unsigned int &_w, const unsigned int &_h, const Rgba &c = kBlack) :
        w(_w), h(_h), pixels(NULL)
    {
        pixels = new Rgba[w * h];
        for (uint i = 0; i < w * h; ++i)
            pixels[i] = c;
    }

    Image(char* filename);

    const Rgba& operator [] (const unsigned int &i) const
    { return pixels[i]; }
    Rgba& operator [] (const unsigned int &i)
    { return pixels[i]; }
    ~Image()
    { if (pixels != NULL) delete [] pixels; }

    QImage getImage();
    void negatify();
    void grayscale();
    void flip_vertical();
    void flip_horizontal();
    void rotate_90_clockwise();
    void rotate_90_c_clockwise();
    void change_brightness(int value);
    void operation_bool(Image *secondImage, bool OR);
    void operation_arithmetic(Image *secondImage);
    void operation_not();
    void transform_gamma(double gamma, int constant);
    void log_transform(const double constant, const bool inverse);
    void graylevel_slicing(int start, int end, bool preserve);
    void zoom(int percentage);
    void bit_slicing(uint kernel);
    void contrast_stretching(int x1, int y1, int x2, int y2);
    void save(char* filename);
    void konvolusi(double kernel[], int dimension, double divident);
    void cross_convolution(double kernel_x[], double kernel_y[], int dimension);
    void roberts();
    void to_biner(int threshold);
    void gradient();
    void update_translate(bool from_ori);
    void reset();


    unsigned int w, h; // Image resolution
    int translate_x = 0, translate_y = 0;
    Rgba *pixels, *pixels_ori; // 1D array of pixels
    static const Rgba kBlack, kWhite, kRed, kGreen, kBlue; // Preset colors

private:

};

#endif // IMAGE_H
