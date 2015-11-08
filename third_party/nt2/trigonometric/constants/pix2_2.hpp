//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_PIX2_2_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_PIX2_2_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief Pix2_2 generic tag

     Represents the Pix2_2 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    // 12.56637061
    BOOST_SIMD_CONSTANT_REGISTER( Pix2_2, double
                                , 1, 0x38daa000
                                , 0x3df0b4611a600000LL
                                )
  }
  /*!
    Constant used in modular computation involving \f$\pi\f$

    @par Semantic:

    For type T0:

    @code
    T0 r = Pix2_2<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pix2_2, Pix2_2);
}

#endif

