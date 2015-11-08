//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_PIX_2_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_PIX_2_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Pix_2 generic tag

     Represents the Pix_2 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Pix_2, double
                                , 6, 0x40c90fdb
                                , 0x401921fb54442d18ll
                                )
  }
  /*!
    Constant  \f$2\pi\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Pix_2<T0>();
    @endcode

    is similar to:

    @code
    T0 r = Pi<T0>()*Two<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pix_2, Pix_2);
}

#endif

