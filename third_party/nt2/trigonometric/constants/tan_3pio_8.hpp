//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_TAN_3PIO_8_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_TAN_3PIO_8_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Tan_3pio_8 generic tag

     Represents the Tan_3pio_8 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Tan_3pio_8, double
                                , 0, 0x401a827aUL
                                , 0x4003504f333f9de6ULL
                                )
  }
  /*!
    Constant \f$\tan3\frac\pi{8} = \sqrt2 + 1\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Tan_3pio_8<T0>();
    @endcode

    is similar to:

    @code
    T0 r = 1.0+sqrt(2.0);
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Tan_3pio_8, Tan_3pio_8);
}

#endif

