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
        Color(uchar luminocity, cuchar a=255);

        uchar luminocity() const;
        uchar perceived_luminocity() const;
        Color with_luminocity(cuchar luminocity) const;
        Color with_perceived_luminocity(cuchar luminocity) const;

        uchar max() const;
        uchar min() const;

        std::tuple<uchar, uchar, uchar> cmy() const;
        static Color from_cmy(uchar c, uchar m, uchar y, uchar a=255);

        uchar hue() const;

        std::tuple<uchar, uchar, uchar> hsv() const;
        static Color from_hsv(uchar h, uchar s, uchar v, uchar a=255);

        std::tuple<uchar, uchar, uchar> hsl() const;
        static Color from_hsl(uchar h, uchar s, uchar l, uchar a=255);

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

            static Color alice_blue;
            static Color antique_white;
            static Color aqua;
            static Color aquamarine;
            static Color azure;
            static Color beige;
            static Color bisque;
            static Color black;
            static Color blanched_almond;
            static Color blue;
            static Color blue_violet;
            static Color brown;
            static Color burly_wood;
            static Color cadet_blue;
            static Color chartreuse;
            static Color chocolate;
            static Color coral;
            static Color cornflower_blue;
            static Color cornsilk;
            static Color crimson;
            static Color cyan;
            static Color dark_blue;
            static Color dark_cyan;
            static Color dark_golden_rod;
            static Color dark_gray;
            static Color dark_grey;
            static Color dark_green;
            static Color dark_khaki;
            static Color dark_magenta;
            static Color dark_olive_green;
            static Color dark_orange;
            static Color dark_orchid;
            static Color dark_red;
            static Color dark_salmon;
            static Color dark_sea_green;
            static Color dark_slate_blue;
            static Color dark_slate_gray;
            static Color dark_slate_grey;
            static Color dark_turquoise;
            static Color dark_violet;
            static Color deep_pink;
            static Color deep_sky_blue;
            static Color dim_gray;
            static Color dim_grey;
            static Color dodger_blue;
            static Color fire_brick;
            static Color floral_white;
            static Color forest_green;
            static Color fuchsia;
            static Color gainsboro;
            static Color ghost_white;
            static Color gold;
            static Color golden_rod;
            static Color gray;
            static Color grey;
            static Color green;
            static Color green_yellow;
            static Color honey_dew;
            static Color hot_pink;
            static Color indian_red;
            static Color indigo;
            static Color ivory;
            static Color khaki;
            static Color lavender;
            static Color lavender_bush;
            static Color lawn_green;
            static Color lemon_chiffon;
            static Color light_blue;
            static Color light_coral;
            static Color light_cyan;
            static Color light_golden_rod_yellow;
            static Color light_gray;
            static Color light_grey;
            static Color light_green;
            static Color light_pink;
            static Color light_salmon;
            static Color light_sea_green;
            static Color light_sky_blue;
            static Color light_slate_gray;
            static Color light_slate_grey;
            static Color light_steel_blue;
            static Color light_yellow;
            static Color lime;
            static Color lime_green;
            static Color linen;
            static Color magenta;
            static Color maroon;
            static Color medium_aqua_marine;
            static Color medium_blue;
            static Color medium_orchid;
            static Color medium_purple;
            static Color medium_sea_green;
            static Color medium_slate_blue;
            static Color medium_spring_green;
            static Color medium_turquoise;
            static Color medium_violet_red;
            static Color midnight_blue;
            static Color mint_cream;
            static Color misty_rose;
            static Color moccasin;
            static Color navajo_white;
            static Color navy;
            static Color old_lace;
            static Color olive;
            static Color olive_drab;
            static Color orange;
            static Color orange_red;
            static Color orchid;
            static Color pale_golden_rod;
            static Color pale_green;
            static Color pale_turquoise;
            static Color pale_violet_red;
            static Color papaya_whip;
            static Color peach_puff;
            static Color peru;
            static Color pink;
            static Color plum;
            static Color powder_blue;
            static Color purple;
            static Color reecca_pruple;
            static Color red;
            static Color rosy_brown;
            static Color royal_blue;
            static Color saddle_brown;
            static Color salmon;
            static Color sandy_brown;
            static Color sea_green;
            static Color sea_shell;
            static Color sienna;
            static Color silver;
            static Color sky_blue;
            static Color slate_blue;
            static Color slate_gray;
            static Color slate_grey;
            static Color snow;
            static Color spring_green;
            static Color steel_blue;
            static Color tan;
            static Color teal;
            static Color thistle;
            static Color tomato;
            static Color turquoise;
            static Color violet;
            static Color wheat;
            static Color white;
            static Color white_smoke;
            static Color yellow;
            static Color yellow_green;
            static Color transparent;
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
