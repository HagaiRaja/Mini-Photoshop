#ifndef IMAGE_H
#define IMAGE_H


class Image
{
public:
    // Rgba structure, i.e. a pixel
    struct Rgba
    {
        Rgba() : r(0), g(0), b(0) {}
        Rgba(float c) : r(c), g(c), b(c) {}
        Rgba(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
        bool operator != (const Rgba &c) const
        { return c.r != r || c.g != g || c.b != b; }
        Rgba& operator *= (const Rgba &rgba)
        { r *= rgba.r, g *= rgba.g, b *= rgba.b; return *this; }
        Rgba& operator += (const Rgba &rgba)
        { r += rgba.r, g += rgba.g, b += rgba.b; return *this; }
        float r, g, b;
    };

    Image() : w(0), h(0), pixels(nullptr) { /* empty image */ }

    Image(const unsigned int &_w, const unsigned int &_h, const Rgba &c = kBlack) :
        w(_w), h(_h), pixels(NULL)
    {
        pixels = new Rgba[w * h];
        for (int i = 0; i < w * h; ++i)
            pixels[i] = c;
    }

    const Rgba& operator [] (const unsigned int &i) const
    { return pixels[i]; }
    Rgba& operator [] (const unsigned int &i)
    { return pixels[i]; }
    ~Image()
    { if (pixels != NULL) delete [] pixels; }
    unsigned int w, h; // Image resolution
    Rgba *pixels; // 1D array of pixels
    static const Rgba kBlack, kWhite, kRed, kGreen, kBlue; // Preset colors

private:

};

#endif // IMAGE_H
