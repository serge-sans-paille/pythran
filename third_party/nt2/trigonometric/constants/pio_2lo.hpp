//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_PIO_2LO_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_PIO_2LO_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Pio_2lo generic tag

     Represents the Pio_2lo constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Pio_2lo, double
                                , 0, 0xb33bbd2eUL
                                , 0x3c91a62633145c07ULL
                                )
  }
  /*!
    This constant is such that, for pairs of types (T, Tup)
    (namely (float,  double) and (double, long double)) the sum:

    abs(Tup(Pio_2lo<T>())+Tup(Pio_2<T>())-Pio_2<Tup>()) is  lesser than
    a few Eps<Tup>().


    This is used to improve accurracy when computing sums of the kind
    \f$\pi/2 + x\f$ with x small,  by replacing them by
    Pio_2 + (Pio_2lo + x)

    @par Semantic:

    For type T0:

    @code
    T r = Pio_2lo<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = 6.123233995736766e-17
    else if T is float
      r = -4.3711388e-08
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pio_2lo, Pio_2lo);
}

#endif

