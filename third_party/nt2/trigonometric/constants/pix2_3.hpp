//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_PIX2_3_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_PIX2_3_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief Pix2_3 generic tag

     Represents the Pix2_3 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    // 12.56637061
    BOOST_SIMD_CONSTANT_REGISTER( Pix2_3, double
                                , 1, 0x31885a30
                                , 0x3bc3198a2e037073ll//3b498a2e03707345ll
                                )
  }
  /*!
    Constant used in modular computation involving \f$\pi\f$

    @par Semantic:

    For type T0:

    @code
    T0 r = Pix2_3<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pix2_3, Pix2_3);
}

#endif

