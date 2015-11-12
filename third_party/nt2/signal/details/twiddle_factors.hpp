//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SIGNAL_DETAILS_TWIDDLE_FACTORS_HPP_INCLUDED
#define NT2_SIGNAL_DETAILS_TWIDDLE_FACTORS_HPP_INCLUDED
#ifdef _MSC_VER
    #pragma once
    #define _USE_MATH_DEFINES
#endif

#include <nt2/signal/details/static_sincos.hpp>

#include <nt2/include/functions/scalar/sincospi.hpp>
#include <nt2/include/functions/simd/sinecosine.hpp>
#include <nt2/include/functions/simd/sincosd.hpp>
#include <nt2/include/functions/simd/sincospi.hpp>
#include <nt2/include/constants/mzero.hpp>

#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/include/functions/simd/enumerate.hpp>

#include <boost/concept_check.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/mul.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#include <math.h>

namespace nt2
{
//------------------------------------------------------------------------------

template <typename T>
struct twiddle_pair
{
    T wr;
    T wi;
};

template <typename T>
struct split_radix_twiddles
{
    twiddle_pair<T> w0;
    twiddle_pair<T> w3;
};


template
<
    unsigned FFTSize,
    typename T
>
struct twiddles_interleaved;
/*
{
    typedef
        BOOST_SIMD_ALIGN_ON( BOOST_SIMD_CONFIG_ALIGNMENT )
        boost::array<twiddle_pair<T> const, fft_size / data_vector_size>
    factors_t;
    static factors_t const factors;
};
*/


////////////////////////////////////////////////////////////////////////////////
// Runtime-static initialisation
//  + simple
//  + compile-time lightweight
//  - does not get placed in the read-only text section
//  - creates dynamic initialisers for each N
//  - forces one of the sincos functions (depending on the used twiddle
//    calculator) to be present in the binary
//  - requires effort to achieve maximum possible precision
////////////////////////////////////////////////////////////////////////////////

namespace detail
{
    ////////////////////////////////////////////////////////////////////////////
    // Twiddle calculator implementations.
    ////////////////////////////////////////////////////////////////////////////
    /// \note Simple radians based sinecosine calculation of twiddles does not
    /// give maximally accurate values because rational values of Pi (a
    /// transcendental number) cannot be represented accurately enough [this
    /// becomes most adverse for inputs which should produce an exact zero, like
    /// cos( Pi/2 )].
    ///                                       (17.07.2012.) (Domagoj Saric)
    ////////////////////////////////////////////////////////////////////////////

    struct twiddle_calculator_scalar
    {
    #ifdef _MSC_VER
        #pragma warning( push )
        #pragma warning( disable : 4510 ) // Default constructor could not be generated.
        #pragma warning( disable : 4512 ) // Assignment operator could not be generated.
        #pragma warning( disable : 4610 ) // Class can never be instantiated - user-defined constructor required.
    #endif
        struct input_t
        {
            long double const omega_scale;
            long double const N          ;
            int         const index      ;
        };
    #ifdef _MSC_VER
        #pragma warning( pop )
    #endif

        template <typename Vector>
        static BOOST_FORCEINLINE input_t generate_input( int const index, long double const omega_scale, long double const N )
        {
            input_t const input = { omega_scale, N, index };
            return input;
        }
    }; // struct twiddle_calculator_scalar

    template <typename Impl>
    struct twiddle_calculator_same_type
    {
        template <typename Vector>
        static BOOST_FORCEINLINE Vector generate_input( int const index, long double const omega_scale, long double const N )
        {
            long double const omega( omega_scale * Impl::full_circle() / N );

            long double const start_value( index * omega );
            long double const increment  (         omega );

            typedef typename Vector::value_type scalar_t;
            Vector const result ( boost::simd::enumerate<Vector>( static_cast<scalar_t>( start_value ), static_cast<scalar_t>( increment ) ) );
            BOOST_ASSERT( result[ Vector::static_size - 1 ] <= omega_scale * Impl::full_circle() / 4 );
            return result;
        }
    };

    struct radians : twiddle_calculator_same_type<radians>
    {
        static long double full_circle() { return 2 * 3.1415926535897932384626433832795028841971693993751058209749445923078164062L; }
        template <typename Vector>
        static BOOST_FORCEINLINE Vector sincos( Vector const & input, Vector & cosine ) { return sinecosine<small_>( input, cosine ); }
    };

    struct degrees : twiddle_calculator_same_type<degrees>
    {
        static long double full_circle() { return 2 * 180; }
        template <typename Vector>
        static BOOST_FORCEINLINE Vector sincos( Vector const & input, Vector & cosine ) { return sincosd( input, cosine ); }
    };

    struct pies : twiddle_calculator_same_type<pies>
    {
        static long double full_circle() { return 2 * 1; }
        template <typename Vector>
        static BOOST_FORCEINLINE Vector sincos( Vector const & input, Vector & cosine ) { return sincospi( input, cosine ); }
    };

    struct pies_scalar_upgraded_type : twiddle_calculator_scalar
    {
        static long double full_circle() { return 2 * 1; }

        template <typename Vector>
        static BOOST_FORCEINLINE Vector sincos( input_t const & input, Vector & cosine )
        {
            typedef typename Vector::value_type scalar_t;

            long double const omega_scale( input.omega_scale );
            long double const N          ( input.N           );
            int         const index      ( input.index       );

            Vector sine;

            for ( int i( 0 ); i < Vector::static_size; ++i )
            {
                //...zzz...should only 'upgrade' float to double and double to long double...
                //...zzz...nt2 doesn't seem to support the long double data type...
                /*long*/ double const omega( ( index + i ) * omega_scale * full_circle() / N );
                /*long*/ double precise_sin;
                /*long*/ double precise_cos;
                nt2::sincospi( omega, precise_sin, precise_cos );

                sine  [ i ] = static_cast<scalar_t>( precise_sin );
                cosine[ i ] = static_cast<scalar_t>( precise_cos );
            }

            return sine;
        }
    };

    struct hardware_or_crt : twiddle_calculator_scalar
    {
        static long double full_circle() { return 2 * 3.1415926535897932384626433832795028841971693993751058209749445923078164062L; }

        template <typename Vector>
        static BOOST_FORCEINLINE Vector sincos( input_t const & input, Vector & cosine )
        {
            Vector sine;

        #if defined( _MSC_VER ) && defined( _M_IX86 )
            Vector::value_type * const p_sine  ( sine  .data() );
            Vector::value_type * const p_cosine( cosine.data() );

            // http://software.intel.com/en-us/forums/showthread.php?t=74354
            // http://www.devmaster.net/forums/showthread.php?t=5784

            unsigned int const vector_size( Vector::static_size );
            long double  const omega_scale( input.omega_scale   );
            long double  const N          ( input.N             );
            unsigned int       local_index( input.index         );
            __asm
            {
                mov ecx, vector_size
                mov edx, p_sine
                mov edi, p_cosine
            sincos_loop:
                fldpi
                fldpi
                fadd
                //...zzz...direct version seems to work the same?
                //fld [omega_scale]
                //fmul
                //fild [local_index]
                //fmul
                //fld [N]
                //fdiv
                fmul  [omega_scale]
                fimul [local_index]
                fdiv  [N]
                fsincos
                fstp [edi]
                add edi, 4
                fstp [edx]
                add edx, 4

                inc [local_index]
                dec ecx
                jnz sincos_loop
            }

        #else // 32 bit x86 MSVC

            long double const omega_scale( input.omega_scale );
            long double const N          ( input.N           );
            int         const index      ( input.index       );

            for ( unsigned i( 0 ); i < Vector::static_size; ++i )
            {
                long double const omega( ( index + i ) * omega_scale * full_circle() / N );

                sine  [ i ] = std::sin( omega );
                cosine[ i ] = std::cos( omega );
            }

        #endif // 32 bit x86 MSVC

            return sine;
        }
    }; // struct hardware_or_crt


#ifdef _MSC_VER
    #pragma warning( push )
    #pragma warning( disable : 4996 ) // '_controlfp': This function or variable may be unsafe.
#endif // _MSC_VER

    /// \note Regardless of the input data layout we always use twiddles
    /// interleaved on vector boundaries in order to improve memory locality and
    /// reduce the number of pointers that must be tracked to help architectures
    /// with a small general purpose register file (32 bit x86 is already
    /// maximally stretched out).
    ///                                       (05.06.2012.) (Domagoj Saric)
    template <typename Vector>
    BOOST_DISPATCH_NOINLINE
    void BOOST_FASTCALL calculate_twiddles
    (
        /// \note Packing these parameters into static const structs (as they
        /// are all known at compile time) proved fruitless because MSVC10 would
        /// either create dynamic initialisers or initialise the objects in
        /// wrong order (since, per the standard, static initialisation order is
        /// completely undefined for templates).
        ///                                   (18.07.2012.) (Domagoj Saric)
        twiddle_pair<Vector> * BOOST_DISPATCH_RESTRICT const p_twiddles,
        unsigned int                                   const N_int,
        unsigned int                                   const stride,
        unsigned int                                   const omega_scale_int,
        unsigned int                                   const start_index
    )
    {
    #if defined( _MSC_VER ) && ( defined( _M_IX86 ) || defined( _M_AMD64 ) || defined( _M_IA64 ) )
        unsigned int const current_precision( ::_controlfp( _PC_64, _MCW_PC ) );
    #endif // _MSC_VER

        twiddle_pair<Vector> * BOOST_DISPATCH_RESTRICT p_w( p_twiddles );

        /// \todo Since cos( a ) = sin( a + Pi/2 ) = -sin( a + 3*Pi/2 ) separate
        /// cos/wr and sin/wi twiddle values could be avoided. The elements of
        /// the array would be half the size (no longer pairs) but there would
        /// have to be extra elements for the cosine offset: N/4 in the first
        /// case (if we store positive sines) or 3N/4 in the second case (if we
        /// store negative sines).
        ///                                   (02.03.2012.) (Domagoj Saric)

        /// \note N/4 values are required for split-radix.
        ///                                   (21.05.2012.) (Domagoj Saric)

        long double const N          ( static_cast<int>( N_int           ) );
        long double const omega_scale( static_cast<int>( omega_scale_int ) );

        unsigned       i        ( start_index             );
        unsigned const end_index( N_int / 4 + start_index );
        while ( i < end_index )
        {
            /// \note The various calculator implementations approximately rank
            /// in this order (from least to most precise):
            /// radians
            /// degrees
            /// hardware_or_crt
            /// pies
            /// pies_scalar_upgraded_type (this requires further investigation).
            ///                               (20.07.2012.) (Domagoj Saric)
            typedef pies impl;

            p_w->wi = impl::sincos( impl::generate_input<Vector>( i, omega_scale, N ), p_w->wr ) ^ Mzero<Vector>();

            i   += Vector::static_size;
            p_w += stride;
        }

        BOOST_ASSERT( p_w == &p_twiddles[ N_int / 4 / Vector::static_size * stride ] );

    #if defined( _MSC_VER ) && ( defined( _M_IX86 ) || defined( _M_AMD64 ) || defined( _M_IA64 ) )
        ::_controlfp( current_precision, _MCW_PC );
    #endif // _MSC_VER
    }

#ifdef _MSC_VER
    #pragma warning( pop )
#endif // _MSC_VER

    template <typename Vector, unsigned N>
    struct twiddle_holder
    {
        twiddle_holder()
        {
            calculate_twiddles<Vector>( &factors.front().w0, N, 2, 1, 0 );
            calculate_twiddles<Vector>( &factors.front().w3, N, 2, 3, 0 );
        }

        typedef
            boost::array
            <
                split_radix_twiddles<Vector> /*const*/,
                N / 4 / Vector::static_size
            >
            factors_t;

        factors_t /*const*/ factors;
    }; // struct twiddle_holder

    template <typename Vector, unsigned N>
    struct real_separation_twiddles_holder
    {
        real_separation_twiddles_holder()
        {
            calculate_twiddles<Vector>( &factors.front(), N, 1, 1, 1 );
        }

        typedef
            boost::array
            <
                twiddle_pair<Vector> /*const*/,
                N / 4 / Vector::static_size
            >
            factors_t;

        factors_t /*const*/ factors;
    }; // struct real_separation_twiddles_holder
} // namespace detail

template <unsigned N, typename Vector>
struct twiddles_interleaved
{
public:
    static split_radix_twiddles<Vector> const * factors() { return twiddles_.factors.begin(); }

private:
    typedef detail::twiddle_holder<Vector, N> twiddle_holder;
    static twiddle_holder const twiddles_;
};

template <unsigned N, typename Vector>
typename twiddles_interleaved<N, Vector>::twiddle_holder const twiddles_interleaved<N, Vector>::twiddles_;


template <unsigned N, typename Vector>
struct real_separation_twiddles
{
public:
    static twiddle_pair<Vector> const * factors() { return twiddles_.factors.begin(); }

private:
    typedef detail::real_separation_twiddles_holder<Vector, N> twiddle_holder;
    static twiddle_holder const twiddles_;
};

template <unsigned N, typename Vector>
typename real_separation_twiddles<N, Vector>::twiddle_holder const real_separation_twiddles<N, Vector>::twiddles_;


//...zzz...the below approaches are still radix-2 specific and use old/ancient
//...zzz...approaches with strides and separate arrays for real and imaginary
//...zzz...parts (so that they don't need to be parameterized with the SIMD data
//...zzz...vector size)...

////////////////////////////////////////////////////////////////////////////////
// Recursive compile-time initialisation
//  + no dynamic initialisers ((hopefully, depending on the compiler)
//  - very compile-time heavyweight (MSVC10 seems to have a template recursion
//    level limit of ~512 so it cannot compile this for FFT sizes >= 2048 even
//    with the recursion "unrolled" into packs of four values)
//  - questionable whether the resulting "array" would still get placed in the
//    text section considering that individual twiddles are not PODs but have
//    default constructors
////////////////////////////////////////////////////////////////////////////////

namespace detail
{
    template
    <
        template <unsigned N, unsigned I> class SinCos,
        unsigned I,
        unsigned N,
        unsigned stride,
        typename T
    >
    struct twiddle
        :
        twiddle<SinCos, I - ( stride * 4 ), N, stride, T>
    {
        twiddle()
            :
            value0( SinCos<N, I - ( stride * 3 )>::value ),
            value1( SinCos<N, I - ( stride * 2 )>::value ),
            value2( SinCos<N, I - ( stride * 1 )>::value ),
            value3( SinCos<N, I - ( stride * 0 )>::value )
        {}

        T const value0;
        T const value1;
        T const value2;
        T const value3;
    };

    template <template <unsigned N, unsigned I> class SinCos, unsigned N, unsigned stride, typename T>
    struct twiddle<SinCos, 0, N, stride, T> {};
} // namespace detail

template <unsigned N, unsigned Stride, typename T>
struct real_twiddles
{
    static float const * factors() { return factors_.begin(); }

    typedef BOOST_SIMD_ALIGN_ON( BOOST_SIMD_CONFIG_ALIGNMENT ) detail::twiddle<static_cosine, N, N, Stride, T> factors_t;
    static factors_t const factors_;
};

template <unsigned N, unsigned Stride, typename T>
typename real_twiddles<N, Stride, T>::factors_t const real_twiddles<N, Stride, T>::factors_;

template <unsigned N, unsigned Stride, typename T>
struct imag_twiddles
{
    static float const * factors() { return factors_.begin(); }

    typedef BOOST_SIMD_ALIGN_ON( BOOST_SIMD_CONFIG_ALIGNMENT ) detail::twiddle<static_sine, N, N, Stride, T> factors_t;
    static factors_t const factors_;
};

template <unsigned N, unsigned Stride, typename T>
typename imag_twiddles<N, Stride, T>::factors_t const imag_twiddles<N, Stride, T>::factors_;


////////////////////////////////////////////////////////////////////////////////
// Preprocessor + compile-time initialisation
//  + fully static
//  + bearable compile-time hit
//  - too heavy on the preprocessor (requires a smarter rewrite to workaround
//    Boost.Preprocessor and compiler limits)
//  - requires in advance definition of explicit specializations for all sizes
//    that will be used in a particular application
////////////////////////////////////////////////////////////////////////////////


#define NT2_AUX_REAL_TWIDDLE( z, i, context )   static_cosine<BOOST_PP_TUPLE_ELEM( 3, 0, context ), i * BOOST_PP_TUPLE_ELEM( 3, 2, context )>::value,
#define NT2_AUX_IMAG_TWIDDLE( z, i, context ) - static_sine  <BOOST_PP_TUPLE_ELEM( 3, 0, context ), i * BOOST_PP_TUPLE_ELEM( 3, 2, context )>::value,

#define NT2_AUX_TWIDDLE( z, i, context )                                                                                                                                                             \
{                                                                                                                                                                                                    \
    { BOOST_PP_REPEAT_FROM_TO( BOOST_PP_MUL( i, BOOST_PP_TUPLE_ELEM( 3, 1, context ) ), BOOST_PP_MUL( BOOST_PP_INC( i ), BOOST_PP_TUPLE_ELEM( 3, 1, context ) ), NT2_AUX_REAL_TWIDDLE, context ) },  \
    { BOOST_PP_REPEAT_FROM_TO( BOOST_PP_MUL( i, BOOST_PP_TUPLE_ELEM( 3, 1, context ) ), BOOST_PP_MUL( BOOST_PP_INC( i ), BOOST_PP_TUPLE_ELEM( 3, 1, context ) ), NT2_AUX_IMAG_TWIDDLE, context ) },  \
},

#define NT2_AUX_TWIDDLES( fft_size, stride )                                               \
template <typename T>                                                                      \
struct twiddles<fft_size, stride, T>                                                       \
{                                                                                          \
    static std::size_t const data_vector_size = twiddle_pair<T>::vector_t::static_size;    \
    typedef BOOST_SIMD_ALIGN_ON( BOOST_SIMD_CONFIG_ALIGNMENT )                             \
    boost::array                                                                           \
    <                                                                                      \
        twiddle_pair<T> const,                                                             \
        fft_size / stride / data_vector_size                                               \
    >                                                                                      \
    factors_t;                                                                             \
    static factors_t const factors;                                                        \
};                                                                                         \
                                                                                           \
template <typename T>                                                                      \
typename twiddles<fft_size, stride, T>::factors_t const                                    \
         twiddles<fft_size, stride, T>::factors =                                          \
{{                                                                                         \
    BOOST_PP_REPEAT                                                                        \
    (                                                                                      \
        BOOST_PP_DIV( BOOST_PP_DIV( fft_size, stride ), data_vector_size ),                \
        NT2_AUX_TWIDDLE,                                                                   \
        ( fft_size, data_vector_size, stride )                                             \
    )                                                                                      \
}}

/* Desired output for for fft_size = 8, data_vector_size = 4, stride = 1:
 *   template
 *   <
 *       unsigned fft_size,
 *       unsigned data_vector_size,
 *       unsigned stride,
 *       typename T
 *   >
 *   typename twiddles<fft_size, data_vector_size, stride, T>::factors_t const
 *            twiddles<fft_size, data_vector_size, stride, T>::factors =
 *   {{
 *       {
 *           {   static_cosine<fft_size, 0 * stride>::value,   static_cosine<fft_size, 1 * stride>::value,   static_cosine<fft_size, 2 * stride>::value,   static_cosine<fft_size, 3 * stride>::value, },
 *           { - static_sine  <fft_size, 0 * stride>::value, - static_sine  <fft_size, 1 * stride>::value, - static_sine  <fft_size, 2 * stride>::value, - static_sine  <fft_size, 3 * stride>::value, },
 *       },
 *       {
 *           {   static_cosine<fft_size, 4 * stride>::value,   static_cosine<fft_size, 5 * stride>::value,   static_cosine<fft_size, 6 * stride>::value,   static_cosine<fft_size, 7 * stride>::value, },
 *           { - static_sine  <fft_size, 4 * stride>::value, - static_sine  <fft_size, 5 * stride>::value, - static_sine  <fft_size, 6 * stride>::value, - static_sine  <fft_size, 7 * stride>::value, },
 *       },
 *   }};
 */

// Broken (breaches Boost.Preprocessor and compiler limits for FFT sizes 256+)...
/*
    NT2_AUX_TWIDDLES(  128, 4, 1 );
    NT2_AUX_TWIDDLES(  128, 4, 2 );
    NT2_AUX_TWIDDLES(  256, 4, 1 );
    NT2_AUX_TWIDDLES(  256, 4, 2 );
    NT2_AUX_TWIDDLES(  512, 4, 1 );
    NT2_AUX_TWIDDLES(  512, 4, 2 );
    NT2_AUX_TWIDDLES( 1024, 4, 1 );
    NT2_AUX_TWIDDLES( 1024, 4, 2 );
    NT2_AUX_TWIDDLES( 2048, 4, 1 );
    NT2_AUX_TWIDDLES( 2048, 4, 2 );
¸*/

//------------------------------------------------------------------------------
} // namespace nt2
//------------------------------------------------------------------------------
#endif // twiddle_factors_hpp
