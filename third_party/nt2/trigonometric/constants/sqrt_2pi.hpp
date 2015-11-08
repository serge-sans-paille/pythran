//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_SQRT_2PI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_SQRT_2PI_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief Sqrt_2pi generic tag

     Represents the Sqrt_2pi constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Sqrt_2pi, double
                                , 2, 0x40206c99
                                , 0x40040d931ff62704ll
                                )
  }
  /*!
    Constant \f$\sqrt{2\pi}\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Sqrt_2pi<T0>();
    @endcode

    is similar to:

    @code
    T0 r = sqrt(Pix2<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Sqrt_2pi, Sqrt_2pi);
}

#endif

