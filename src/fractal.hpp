
#pragma once
#include <complex>
namespace Fractal
{

struct view
{
    int plot_width;
    int plot_height;
    int depth;
    std::complex<double> center = {-0.8, 0};
    double scale = (3.0 / 800);
    double aspect = 1.0;
};

inline bool operator==(const view& lhs, const view& rhs)
{
    return (lhs.center == rhs.center)
        && (lhs.scale == rhs.scale)
        && (lhs.depth == rhs.depth);
}

// Function to draw mandelbrot set
template <typename PLOT>
void mandlebrot(const view& v, PLOT plot)
{
    // setting up the xscale and yscale
    double xscale = v.scale * v.aspect;
    double yscale = v.scale;
    double left = v.center.real() - (xscale * v.plot_width * 0.5);
    double top = v.center.imag() + (yscale * v.plot_height * 0.5);


    // scanning every point in that rectangular area.
    // Each point represents a Complex number (x + yi).
    // Iterate that complex number
    for (int y = 0; y < v.plot_height; y++)
    {
        for (int x = 0; x < v.plot_width; x++)
        {
            std::complex<double> c(left + x * xscale, top - y * yscale);
            std::complex<double> z(0.0, 0.0);
            int count = 0;
            while (count < v.depth)
            {
                z = z * z + c;
                if (abs(z) > 2.0)
                    break;
                ++count;
            }

            // To display the created fractal
            plot(x, y, count);
        }
    }
}
}