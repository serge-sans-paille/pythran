//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SIGNAL_DETAILS_STATIC_SINCOS_HPP_INCLUDED
#define NT2_SIGNAL_DETAILS_STATIC_SINCOS_HPP_INCLUDED
#pragma once

#include <math.h>

namespace nt2
{
////////////////////////////////////////////////////////////////////////////////
// Static sin/cos routines from the Dr.Dobbs article (generic but very slow at
// compile-time).
// http://drdobbs.com/cpp/199500857
////////////////////////////////////////////////////////////////////////////////

namespace detail
{
    template <unsigned M, unsigned N, unsigned B, unsigned A>
    struct static_sin_cos
    {
        static double value() { return 1 - ( A*M_PI/B ) * ( A*M_PI/B ) / M / ( M+1 ) * static_sin_cos<M+2, N, B, A>::value(); }
    };

    template <unsigned N, unsigned B, unsigned A>
    struct static_sin_cos<N, N, B, A> { static double value() { return 1; } };
} // namespace detail


template <unsigned B, unsigned A, typename T=double>
struct static_sin;

template <unsigned B, unsigned A>
struct static_sin<B, A, float>
{
    static float value() { return static_cast<float>( ( A*M_PI/B ) * detail::static_sin_cos<2, 24, B, A>::value() ); }
};

template <unsigned B, unsigned A>
struct static_sin<B, A, double>
{
    static double value() { return ( A*M_PI/B ) * detail::static_sin_cos<2, 34, B, A>::value(); }
};

template <unsigned B, unsigned A>
struct static_sin<B, A, long double>
{
    static long double value() { return ( A*M_PI/B ) * detail::static_sin_cos<2, 60, B, A>::value(); }
};

template <unsigned B, unsigned A, typename T=double>
struct static_cos;

template <unsigned B, unsigned A>
struct static_cos<B, A, float>
{
    static float value() { return static_cast<float>( detail::static_sin_cos<1, 23, B, A>::value() ); }
};

template <unsigned B, unsigned A>
struct static_cos<B, A, double>
{
    static double value() { return detail::static_sin_cos<1, 33, B, A>::value(); }
};

template <unsigned B, unsigned A>
struct static_cos<B, A, long double>
{
    static double value() { return detail::static_sin_cos<1, 60, B, A>::value(); }
};


////////////////////////////////////////////////////////////////////////////////
// Todd Veldhuizen's direct, single precision, significantly compile-time faster
// routines.
// http://www.oonumerics.org/blitz/examples/fft.html
////////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned I>
struct static_sine
{
    static float const value;
};

template <unsigned N, unsigned I>
float const static_sine<N, I>::value
(
    // Series expansion for sin( I*2*M_PI/N ):
    static_cast<float>
    (
        (I*2*M_PI/N)      *(1-(I*2*M_PI/N)*(I*2*M_PI/N)/ 2/ 3*(1-(I*2*M_PI/N)*
        (I*2*M_PI/N)/ 4/ 5*(1-(I*2*M_PI/N)*(I*2*M_PI/N)/ 6/ 7*(1-(I*2*M_PI/N)*
        (I*2*M_PI/N)/ 8/ 9*(1-(I*2*M_PI/N)*(I*2*M_PI/N)/10/11*(1-(I*2*M_PI/N)*
        (I*2*M_PI/N)/12/13*(1-(I*2*M_PI/N)*(I*2*M_PI/N)/14/15*
        (1-(I*2*M_PI/N)*(I*2*M_PI/N)/16/17*
        (1-(I*2*M_PI/N)*(I*2*M_PI/N)/18/19*(1-(I*2*M_PI/N)*
        (I*2*M_PI/N)/20/21))))))))))
    )
);


template <unsigned N, unsigned I>
struct static_cosine
{
    static float const value;
};

template <unsigned N, unsigned I>
float const static_cosine<N ,I>::value
(
    // Series expansion for cos( I*2*M_PI/N ):
    static_cast<float>
    (
         1-(I*2*M_PI/N)*(I*2*M_PI/N)    /2*(1-(I*2*M_PI/N)*(I*2*M_PI/N)/ 3/ 4*
        (1-(I*2*M_PI/N)*(I*2*M_PI/N)/ 5/ 6*(1-(I*2*M_PI/N)*(I*2*M_PI/N)/ 7/ 8*
        (1-(I*2*M_PI/N)*(I*2*M_PI/N)/ 9/10*(1-(I*2*M_PI/N)*(I*2*M_PI/N)/11/12*
        (1-(I*2*M_PI/N)*(I*2*M_PI/N)/13/14*(1-(I*2*M_PI/N)*(I*2*M_PI/N)/15/16*
        (1-(I*2*M_PI/N)*(I*2*M_PI/N)/17/18*(1-(I*2*M_PI/N)*(I*2*M_PI/N)/19/20*
        (1-(I*2*M_PI/N)*(I*2*M_PI/N)/21/22*(1-(I*2*M_PI/N)*(I*2*M_PI/N)/23/24
        )))))))))))
    )
);

} // namespace nt2

#endif // static_sincos_hpp
