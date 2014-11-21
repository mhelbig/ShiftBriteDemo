typedef struct RgbColor
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
} RgbColor;

typedef struct HsvColor
{
    unsigned int h;
    unsigned int s;
    unsigned int v;
} HsvColor;

RgbColor HsvToRgb(HsvColor hsv);
HsvColor RgbToHsv(RgbColor rgb);

