#ifndef SFML_UTILS_CONVERTER_HPP
#define SFML_UTILS_CONVERTER_HPP


namespace sfutils
{
    namespace converter
    {
        constexpr double PIXELS_PER_METERS = 32.0;
        constexpr double PI = 3.14159265358979323846;

        template<typename T>
        constexpr T pixel_to_meters(const T& x)
        {
            return x/PIXELS_PER_METERS;
        };

        template<typename T>
        constexpr T meters_to_pixels(const T& x)
        {
            return x*PIXELS_PER_METERS;
        };

        template<typename T>
        constexpr T deg_to_rad(const T& x)
        {
            return PI*x/180.0;
        };

        template<typename T>
        constexpr T rad_to_deg(const T& x)
        {
            return 180.0*x/PI;
        }

    }
}
#endif
