// jul.cpp - 2016.05.09 - Atlee Brink
// filled Julia set plotter

#include "nimg.hpp"

#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <iostream>
#include <random>
#include <vector>

namespace {
    using namespace nimg;
    using namespace std;
    using namespace std::complex_literals;

    // rendering parameters
    const int N = 50; // max iterations
    const srgba background = {255, 255, 255, 255};
    const srgba_light light = {-255, -255, -255, 0};

    // default C constant
    complex<double> C(-0.76, 0.1);
}

int main() {

    const int w = 2048, h = 2048;
    cout << "allocating memory for a " << w << " x " << h << " image buffer..." << flush;
    simg img( w, h, background );
    cout << " done." << endl;

    double threshold = max( abs(C), 2.0 );

    // do a render
    cout << "rendering..." << flush;
    const double xinc = 4.0 / w, yinc = 4.0 / h;
    for( int x = 0; x < w; x++ ) {
        for( int y = 0; y < h; y++ ) {
            bool stayed = true;
            complex<double> z( x * xinc - 2.0, y * yinc - 2.0 );
            for( int n = 0; n < N; n++ ) {
                if( abs(z) > threshold ) {
                    stayed = false;
                    break;
                }
                z = z*z + C;
            }
            if( stayed ) img.add( x, y, light );
        }
    }
    cout << " done." << endl;

    char filename[1024];
    sprintf( filename, "Q(z)=z*z+%g+%gi_%ux%u.png", C.real(), C.imag(), w, h );

    img.save( string(filename) );

    return 0;
}
