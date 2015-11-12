//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_PIO_4LO_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_PIO_4LO_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Pio_4lo generic tag

     Represents the Pio_4lo constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Pio_4lo, double
                                , 0, 0xb2bbbd2eUL
                                , 0x3c81a62633145c07ULL
                                )
  }
  /*!
    This constant is such that, for pairs of types (Tup, T)
    (namely (float,  double) and (double, long double)) the sum:

    abs(Tup(Pio_4lo<T>())+Tup(Pio_4<T>())-Pio_4<Tup>())  is  lesser than
    a few Eps<Tup>().

    This is used to improve accurracy when computing sums of the kind
    Pio_4 + x with x small,  by replacing them by Pio_4 + (Pio_4lo+x)

    @par Semantic:

    For type T0:

    @code
    T r = Pio_4lo<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = 3.061616997868383e-17
    else if T is float
      r = -2.1855694e-08
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pio_4lo, Pio_4lo);
}

#endif

