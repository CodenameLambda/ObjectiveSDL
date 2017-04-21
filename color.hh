#ifndef OBJSDL_COLOR_HH
#define OBJSDL_COLOR_HH

#include <tuple>
#include "short_types.hh"


namespace SDL {
    namespace _implementation {
        namespace color {
            enum BlendMode {
                normal,
                multiply,
                screen,
                overlay,
                hard_light,
                soft_light_photoshop,
                soft_light_pegtop,
                soft_light_illusions_hu,
                soft_light_w3c,
                color_dodge,
                linear_dodge,
                divide,
                color_burn,
                linear_burn,
                vivid_light,
                linear_light,
                subtract,
                add,
                difference,
                darken_only,
                lighten_only,
                hue,
                saturation,
                color,
                perceived_luminocity_color,
                luminocity,
                perceived_luminocity,
                alpha_compositing,
                average
            };
        }
    }

    struct Color {
        uchar r;
        uchar g;
        uchar b;
        uchar a;

        Color();  // black
        Color(cuchar r, cuchar g, cuchar b, cuchar a=255);
        Color(cuchar luminocity, cuchar a=255);

        uchar luminocity() const;
        uchar perceived_luminocity() const;
        Color with_luminocity(cuchar luminocity) const;
        Color with_perceived_luminocity(cuchar luminocity) const;

        uchar max() const;
        uchar min() const;

        std::tuple<uchar, uchar, uchar> cmy() const;
        static Color from_cmy(cuchar c, cuchar m, cuchar y, cuchar a=255);

        uchar hue() const;

        std::tuple<uchar, uchar, uchar> hsv() const;
        static Color from_hsv(cuchar h, cuchar s, cuchar v, cuchar a=255);

        std::tuple<uchar, uchar, uchar> hsl() const;
        static Color from_hsl(cuchar h, cuchar s, cuchar l, cuchar a=255);

        Color inverted() const;

        Color with_alpha(cuchar alpha) const;
        Color opaque() const;

        using BlendMode = _implementation::color::BlendMode;

        static Color blend(
                const Color bottom,
                const Color top,
                const BlendMode mode=BlendMode::alpha_compositing
        );

        struct colors {  // namespace
            colors();  // raises error.

            static const Color alice_blue;
            static const Color antique_white;
            static const Color aqua;
            static const Color aquamarine;
            static const Color azure;
            static const Color beige;
            static const Color bisque;
            static const Color black;
            static const Color blanched_almond;
            static const Color blue;
            static const Color blue_violet;
            static const Color brown;
            static const Color burly_wood;
            static const Color cadet_blue;
            static const Color chartreuse;
            static const Color chocolate;
            static const Color coral;
            static const Color cornflower_blue;
            static const Color cornsilk;
            static const Color crimson;
            static const Color cyan;
            static const Color dark_blue;
            static const Color dark_cyan;
            static const Color dark_golden_rod;
            static const Color dark_gray;
            static const Color dark_grey;
            static const Color dark_green;
            static const Color dark_khaki;
            static const Color dark_magenta;
            static const Color dark_olive_green;
            static const Color dark_orange;
            static const Color dark_orchid;
            static const Color dark_red;
            static const Color dark_salmon;
            static const Color dark_sea_green;
            static const Color dark_slate_blue;
            static const Color dark_slate_gray;
            static const Color dark_slate_grey;
            static const Color dark_turquoise;
            static const Color dark_violet;
            static const Color deep_pink;
            static const Color deep_sky_blue;
            static const Color dim_gray;
            static const Color dim_grey;
            static const Color dodger_blue;
            static const Color fire_brick;
            static const Color floral_white;
            static const Color forest_green;
            static const Color fuchsia;
            static const Color gainsboro;
            static const Color ghost_white;
            static const Color gold;
            static const Color golden_rod;
            static const Color gray;
            static const Color grey;
            static const Color green;
            static const Color green_yellow;
            static const Color honey_dew;
            static const Color hot_pink;
            static const Color indian_red;
            static const Color indigo;
            static const Color ivory;
            static const Color khaki;
            static const Color lavender;
            static const Color lavender_bush;
            static const Color lawn_green;
            static const Color lemon_chiffon;
            static const Color light_blue;
            static const Color light_coral;
            static const Color light_cyan;
            static const Color light_golden_rod_yellow;
            static const Color light_gray;
            static const Color light_grey;
            static const Color light_green;
            static const Color light_pink;
            static const Color light_salmon;
            static const Color light_sea_green;
            static const Color light_sky_blue;
            static const Color light_slate_gray;
            static const Color light_slate_grey;
            static const Color light_steel_blue;
            static const Color light_yellow;
            static const Color lime;
            static const Color lime_green;
            static const Color linen;
            static const Color magenta;
            static const Color maroon;
            static const Color medium_aqua_marine;
            static const Color medium_blue;
            static const Color medium_orchid;
            static const Color medium_purple;
            static const Color medium_sea_green;
            static const Color medium_slate_blue;
            static const Color medium_spring_green;
            static const Color medium_turquoise;
            static const Color medium_violet_red;
            static const Color midnight_blue;
            static const Color mint_cream;
            static const Color misty_rose;
            static const Color moccasin;
            static const Color navajo_white;
            static const Color navy;
            static const Color old_lace;
            static const Color olive;
            static const Color olive_drab;
            static const Color orange;
            static const Color orange_red;
            static const Color orchid;
            static const Color pale_golden_rod;
            static const Color pale_green;
            static const Color pale_turquoise;
            static const Color pale_violet_red;
            static const Color papaya_whip;
            static const Color peach_puff;
            static const Color peru;
            static const Color pink;
            static const Color plum;
            static const Color powder_blue;
            static const Color purple;
            static const Color reecca_pruple;
            static const Color red;
            static const Color rosy_brown;
            static const Color royal_blue;
            static const Color saddle_brown;
            static const Color salmon;
            static const Color sandy_brown;
            static const Color sea_green;
            static const Color sea_shell;
            static const Color sienna;
            static const Color silver;
            static const Color sky_blue;
            static const Color slate_blue;
            static const Color slate_gray;
            static const Color slate_grey;
            static const Color snow;
            static const Color spring_green;
            static const Color steel_blue;
            static const Color tan;
            static const Color teal;
            static const Color thistle;
            static const Color tomato;
            static const Color turquoise;
            static const Color violet;
            static const Color wheat;
            static const Color white;
            static const Color white_smoke;
            static const Color yellow;
            static const Color yellow_green;
            static const Color transparent;
        };
    };

    Color operator+(const Color, const Color);
    Color operator-(const Color, const Color);
    Color operator*(const Color, const Color);
    Color operator/(const Color, const Color);
    Color operator*(cfloat, const Color);
    Color operator*(const Color, cfloat);
    Color operator/(const Color, cfloat);
}

#endif
