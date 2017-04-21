#include "color.hh"
#include <cmath>


namespace SDL {
    namespace _implementation {
        namespace color {
            uchar abs(short x) {
                if (x >= 0)
                    return x;
                else
                    return -x;
            }

            uchar hue2rgb(cuchar p, cuchar q, cuchar t) {
                if (float(t) < 42.5f)
                    return float(p) + float(q - p) * 6.f * float(t) / 255.f;
                else if (float(t) < 127.5f)
                    return q;
                else if (t < 170)
                    return float(p) + float(q - p) * (2.f/3.f - float(t) / 255.f) * 6.f;
                else
                    return p;
            }

            uchar overlay_channel(cuchar a, cuchar b) {
                if (float(a) < 127.5f)
                    return 2 * short(a) * short(b) / 255;
                else
                    return 255 - uchar(2*short(255 - a)*short(255 - b) / 255);
            }

            uchar soft_light_photoshop_channel(cuchar a, cuchar b) {
                if (float(b) < 127.5f)
                    return 2 * short(a) * short(b) / 255 +
                        short(a) * short(a) * (255 - 2 * short(b)) / (255 * 255);
                else
                    return short(
                        2. * double(a) * (255. - double(b)) / 255. +
                        std::sqrt(double(a) / 255.) * (2. * double(b) - 255.)
                    );
            }

            uchar soft_light_pegtop_channel(cuchar a, cuchar b) {
                return ((255 - 2*short(b)) * short(a) * short(a) + 2*short(a)*short(b)*255) / 255;
            }

            uchar soft_light_illusions_hu_channel(cuchar a, cuchar b) {
                return 255 * std::pow(
                    double(a) / 255.,
                    std::pow(2., 2.*(127.5 - double(b)) / 255.)
                );
            }

            double g_w3c(double a) {
                a = a / 255.;
                if (a <= 0.25)
                    return ((16. * a - 12) * a + 4) * a;
                else
                    return std::sqrt(a);
            }

            uchar soft_light_w3c_channel(cuchar a, cuchar b) {
                if (float(b) <= 127.f)
                    return (
                        short(a) * 255 * 255 -
                        (255 - 2*short(b)) * short(a) * (255 - short(a))
                    ) / (255 * 255);
                else
                    return a + uchar(short((2 * double(b) - 255) * (g_w3c(a) - double(a)/255.)));
            }

            uchar min(cuchar a, cuchar b) {
                return (a > b) ? b : a;
            }

            uchar max(cuchar a, cuchar b) {
                return (a > b) ? a : b;
            }
        }
    }

    Color::Color() {
        this->r = 0;
        this->g = 0;
        this->b = 0;
        this->a = 255;
    }

    Color::Color(cuchar r, cuchar g, cuchar b, cuchar a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color::Color(uchar luminocity, cuchar a) {
        this->r = luminocity;
        this->g = luminocity;
        this->b = luminocity;
        this->a = a;
    }

    uchar Color::luminocity() const {
        return (ushort(this->r) + ushort(this->g) + ushort(this->b)) / 3;
    }

    uchar Color::perceived_luminocity() const {
        return 0.2126f * float(this->r) + 0.7152f * float(this->g) + 0.0722f * float(this->b);
    }

    Color Color::with_luminocity(cuchar luminocity) const {
        return (float(luminocity) / float(this->luminocity())) * (*this);
    }

    Color Color::with_perceived_luminocity(cuchar luminocity) const {
        return (float(luminocity) / float(this->perceived_luminocity())) * (*this);
    }

    uchar Color::max() const {
        uchar out = 0;

        for (cuchar value : {this->r, this->g, this->b})
            if (value > out)
                out = value;

        return out;
    }

    uchar Color::min() const {
        uchar out = 255;

        for (cuchar value : {this->r, this->g, this->b})
            if (value < out)
                out = value;

        return out;
    }

    std::tuple<uchar, uchar, uchar> Color::cmy() const {
        return {255 - this->r, 255 - this->g, 255 - this->b};
    }

    Color Color::from_cmy(uchar c, uchar m, uchar y, uchar a) {
        return Color(255 - c, 255 - m, 255 - y, a);
    }

    uchar hue(const Color c, cuchar min, cuchar max) {
        uchar h;
        if (min == max)
            h = 0;
        else if (max == c.r)
            h = char(42.5f * (0.f + float(c.g - c.b) / float(max - min)));
        else if (max == c.g)
            h = char(42.5f * (2.f + float(c.b - c.r) / float(max - min)));
        else // max == c.b
            h = char(42.5f * (2.f + float(c.r - c.g) / float(max - min)));

        return h;
    }

    uchar Color::hue() const {
        return SDL::hue(*this, this->min(), this->max());
    }

    std::tuple<uchar, uchar, uchar> Color::hsv() const {
        cuchar min = this->min();
        cuchar max = this->max();
        cuchar h = SDL::hue(*this, min, max);
        cuchar s = max == 0? 0 : (max - min) / max;
        cuchar v = max;
        return {h, s, v};
    }

    Color Color::from_hsv(uchar h, uchar s, uchar v, uchar a) {
        if (s == 0)
            return {v, v, v};

        uchar hi = float(h) / 42.5f;
        float f = float(h) / 42.5f - float(hi);
        uchar p = float(v) * (255.f - float(s)) / 255.f;
        uchar q = float(v) * (255.f - float(s) * f) / 255.f;
        uchar t = float(v) * (255.f - float(s) * (1.f - f)) / 255.f;
        switch (hi) {
            case 0:
            case 6:
                return {v, t, p};
            case 1:
                return {q, v, p};
            case 2:
                return {p, v, t};
            case 3:
                return {p, q, v};
            case 4:
                return {t, p, v};
            default:  // hi == 5
                return {v, p, q};
        }
    }

    std::tuple<uchar, uchar, uchar> Color::hsl() const {
        cuchar min = this->min();
        cuchar max = this->max();

        cuchar h = SDL::hue(*this, min, max);
        uchar s;
        if (max == 0)
            s = 0;
        else if (min == 1)
            s = 0;
        else
            s = float(max - min) /
                float(
                        255 -
                        _implementation::color::abs(
                            short(max) + short(min) - 255
                        )
                );

        cuchar l = (short(max) + short(min)) / 2;
        return {h, s, l};
    }

    Color Color::from_hsl(uchar h, uchar s, uchar l, uchar a) {
        if (s == 0)
            return {l, l, l};

        uchar q;
        if (float(l) < 127.5)
            q = short(l) * short(255 + s) / 255;
        else
            q = (short(l)*255 + short(s)*255 - short(l * s)) / 255;

        cuchar p = 2 * short(l) - short(q);

        return {
            _implementation::color::hue2rgb(p, q, short(float(h) + 255.f/3.f)),
            _implementation::color::hue2rgb(p, q, h),
            _implementation::color::hue2rgb(p, q, short(float(h) - 255.f/3.f))
        };
    }

    Color Color::inverted() const {
        return Color(255 - this->r, 255 - this->g, 255 - this->b, 255 - this->a);
    }

    Color Color::with_alpha(cuchar alpha) const {
        return Color(this->r, this->g, this->b, alpha);
    }

    Color Color::opaque() const {
        return Color(this->r, this->g, this->b);
    }

    Color Color::blend(const Color bottom, const Color top, const BlendMode mode) {
        switch (mode) {
            case BlendMode::normal:
                return top;
            case BlendMode::multiply:
                return {
                    uchar((short(top.r) * short(bottom.r)) / 255),
                    uchar((short(top.g) * short(bottom.g)) / 255),
                    uchar((short(top.b) * short(bottom.b)) / 255),
                    uchar((short(top.a) * short(bottom.a)) / 255)
                };
            case BlendMode::screen:
                return Color::blend(bottom.inverted(), top.inverted()).inverted();
            case BlendMode::overlay:
                return {
                    _implementation::color::overlay_channel(bottom.r, top.r),
                    _implementation::color::overlay_channel(bottom.g, top.g),
                    _implementation::color::overlay_channel(bottom.b, top.b),
                    _implementation::color::overlay_channel(bottom.a, top.a)
                };
            case BlendMode::hard_light:
                return Color::blend(top, bottom, BlendMode::overlay);
            case BlendMode::soft_light_photoshop:
                return {
                    _implementation::color::soft_light_photoshop_channel(bottom.r, top.r),
                    _implementation::color::soft_light_photoshop_channel(bottom.g, top.g),
                    _implementation::color::soft_light_photoshop_channel(bottom.b, top.b),
                    _implementation::color::soft_light_photoshop_channel(bottom.a, top.a)
                };
            case BlendMode::soft_light_pegtop:
                return {
                    _implementation::color::soft_light_pegtop_channel(bottom.r, top.r),
                    _implementation::color::soft_light_pegtop_channel(bottom.g, top.g),
                    _implementation::color::soft_light_pegtop_channel(bottom.b, top.b),
                    _implementation::color::soft_light_pegtop_channel(bottom.a, top.a)
                };
            case BlendMode::soft_light_illusions_hu:
                return {
                    _implementation::color::soft_light_illusions_hu_channel(bottom.r, top.r),
                    _implementation::color::soft_light_illusions_hu_channel(bottom.g, top.g),
                    _implementation::color::soft_light_illusions_hu_channel(bottom.b, top.b),
                    _implementation::color::soft_light_illusions_hu_channel(bottom.a, top.a)
                };
            case BlendMode::soft_light_w3c:
                return {
                    _implementation::color::soft_light_w3c_channel(bottom.r, top.r),
                    _implementation::color::soft_light_w3c_channel(bottom.g, top.g),
                    _implementation::color::soft_light_w3c_channel(bottom.b, top.b),
                    _implementation::color::soft_light_w3c_channel(bottom.a, top.a)
                };
            case BlendMode::color_dodge:
                return Color::blend(bottom, top.inverted(), BlendMode::divide);
            case BlendMode::linear_dodge:
                return Color::blend(bottom, top, BlendMode::add);
            case BlendMode::divide:
                return {
                    (top.r == 0) ? uchar(255) : uchar(bottom.r / top.r),
                    (top.g == 0) ? uchar(255) : uchar(bottom.g / top.g),
                    (top.b == 0) ? uchar(255) : uchar(bottom.b / top.b),
                    (top.a == 0) ? uchar(255) : uchar(bottom.a / top.a)
                };
            case BlendMode::color_burn:
                return Color::blend(bottom.inverted(), top, BlendMode::divide).inverted();
            case BlendMode::linear_burn:
                return {
                    uchar(short(bottom.r) + short(top.r) - 255),
                    uchar(short(bottom.g) + short(top.g) - 255),
                    uchar(short(bottom.b) + short(top.b) - 255),
                    uchar(short(bottom.a) + short(top.a) - 255)
                };
            case BlendMode::vivid_light:
                if (top.luminocity() > 0.5)
                    return Color::blend(bottom, top, BlendMode::color_dodge);
                else
                    return Color::blend(bottom, top, BlendMode::color_burn);
            case BlendMode::linear_light:
                if (top.luminocity() > 0.5)
                    return Color::blend(bottom, top, BlendMode::linear_dodge);
                else
                    return Color::blend(bottom, top, BlendMode::linear_burn);
            case BlendMode::subtract:
                return {
                    (bottom.r > top.r) ? uchar(bottom.r - top.r) : uchar(0),
                    (bottom.g > top.g) ? uchar(bottom.g - top.g) : uchar(0),
                    (bottom.b > top.b) ? uchar(bottom.b - top.b) : uchar(0),
                    (bottom.a > top.a) ? uchar(bottom.a - top.a) : uchar(0)
                };
            case BlendMode::add:
                return {
                    (short(bottom.r) + short(top.r) < 255) ? uchar(bottom.r + top.r) : uchar(255),
                    (short(bottom.g) + short(top.g) < 255) ? uchar(bottom.g + top.g) : uchar(255),
                    (short(bottom.b) + short(top.b) < 255) ? uchar(bottom.b + top.b) : uchar(255),
                    (short(bottom.a) + short(top.a) < 255) ? uchar(bottom.a + top.a) : uchar(255)
                };
            case BlendMode::difference:
                return {
                    _implementation::color::abs(short(bottom.r) - short(top.r)),
                    _implementation::color::abs(short(bottom.g) - short(top.g)),
                    _implementation::color::abs(short(bottom.b) - short(top.b)),
                    _implementation::color::abs(short(bottom.a) - short(top.a))
                };
            case BlendMode::darken_only:
                return {
                    _implementation::color::min(bottom.r, top.r),
                    _implementation::color::min(bottom.g, top.g),
                    _implementation::color::min(bottom.b, top.b),
                    _implementation::color::min(bottom.a, top.a)
                };
            case BlendMode::lighten_only:
                return {
                    _implementation::color::max(bottom.r, top.r),
                    _implementation::color::max(bottom.g, top.g),
                    _implementation::color::max(bottom.b, top.b),
                    _implementation::color::max(bottom.a, top.a)
                };
            case BlendMode::hue:
                {
                    const auto hsv = bottom.hsv();
                    return Color::from_hsv(
                        top.hue(),
                        std::get<1>(hsv),
                        std::get<2>(hsv),
                        bottom.a
                    );
                }
            case BlendMode::saturation:
                {
                    const auto hsv = bottom.hsv();
                    return Color::from_hsv(
                        std::get<0>(hsv),
                        std::get<1>(top.hsv()),
                        std::get<2>(hsv),
                        bottom.a
                    );
                }
            case BlendMode::color:
                return top.with_luminocity(bottom.luminocity());
            case BlendMode::perceived_luminocity_color:
                return top.with_perceived_luminocity(bottom.perceived_luminocity());
            case BlendMode::luminocity:
                return bottom.with_luminocity(top.luminocity());
            case BlendMode::perceived_luminocity:
                return bottom.with_perceived_luminocity(top.perceived_luminocity());
            default:  // mode == BlendMode::average
                return {
                    uchar((short(top.r) + short(bottom.r)) / 2),
                    uchar((short(top.g) + short(bottom.g)) / 2),
                    uchar((short(top.b) + short(bottom.b)) / 2),
                    uchar((short(top.a) + short(bottom.a)) / 2)
                };
        }
    }

    Color operator+(const Color bottom, const Color top) {
        return Color::blend(bottom, top, Color::BlendMode::add);
    }

    Color operator-(const Color bottom, const Color top) {
        return Color::blend(bottom, top, Color::BlendMode::subtract);
    }

    Color operator*(const Color bottom, const Color top) {
        return Color::blend(bottom, top, Color::BlendMode::multiply);
    }

    Color operator/(const Color bottom, const Color top) {
        return Color::blend(bottom, top, Color::BlendMode::divide);
    }

    Color operator*(cfloat scalar, const Color c) {
        return Color(
            scalar * float(c.r),
            scalar * float(c.g),
            scalar * float(c.b),
            scalar * float(c.a)
        );
    }

    Color operator*(const Color c, cfloat scalar) {
        return scalar * c;
    }

    Color operator/(const Color c, cfloat scalar) {
        return Color(
            float(c.r) / scalar,
            float(c.g) / scalar,
            float(c.b) / scalar,
            float(c.a) / scalar
        );
    }

    Color::colors::colors() {
        throw nullptr;
    }
}
