//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_PIX_4_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_PIX_4_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Pix_4 generic tag

     Represents the Pix_4 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Pix_4, double
                                , 12, 0x41490fdb
                                , 0x402921fb54442d18ll
                                )
  }
  /*!
    Constant \f$4\pi\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Pix_4<T0>();
    @endcode

    is similar to:

    @code
    T0 r = Pi<T0>()*Four<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pix_4, Pix_4);
}

#endif

