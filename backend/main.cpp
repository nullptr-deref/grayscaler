#include <iostream>
#include <cmath>

#include <QImage>

std::array<float, 3> gammaExpand(const QColor &color) {
    const std::array<float, 3> colors = { color.redF(), color.greenF(), color.blueF() };
    std::array<float, 3> res;
    for (int i = 0; i < 3; i++) {
        res[i] = colors[i] <= .04045
            ? colors[i] / 12.92
            : std::pow((colors[i] + .055)/1.055, 2.4);
    }

    return res;
}

float linearize(const std::array<float, 3> &luminance) {
    return .2126 * luminance[0] + .7152 * luminance[1] + .0722 * luminance[2];
}

std::array<float, 3> gammaCompress(const float linLuminance) {
    std::array<float, 3> compressed;
    for (int i = 0; i < 3; i++) {
        compressed[i] = linLuminance <= .0031308
            ? 12.92 * linLuminance
            : 1.055 * std::pow(linLuminance, 1/2.4) - .055;
    }

    return compressed;
}

QImage grayscale(const QImage *img) {
    QImage res(img->size(), img->format());
    for (int x = 0; x < res.width(); x++) {
        for (int y = 0; y < res.height(); y++) {
            const auto grayed = gammaCompress(linearize(gammaExpand(img->pixel(x, y))));
            res.setPixelColor({x, y}, QColor {
                static_cast<int>(grayed[0] * 255),
                static_cast<int>(grayed[1] * 255),
                static_cast<int>(grayed[2] * 255)
            });
        }
    }

    return res;
}

int main() {
    QImage *src = new QImage("/home/militarycoder/wallpapers/Yosemite.jpg");
    const QImage grayscaled = grayscale(src);
    grayscaled.save("/home/militarycoder/Pictures/grayscaled.jpg");

    return 0;
}
