//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_MEDIUM_PI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_MEDIUM_PI_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief Medium_pi generic tag

     Represents the Medium_pi constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Medium_pi, double
                                , 201, 0x43490fdb       //2^6/pi
                                , 0x412921fb54442d18ll  //2^{18}/pi
                                )
  }
  /*!
    Constant used in trigonometric reductions

    @par Semantic:

    For type T0:

    @code
    T0 r = Medium_pi<T0>();
    @endcode

    is similar to:

    @code
    if T is double
      r = Pi<T0>()*pow2(18);
    else if T is float
      r = Pi<T0>()*pow2(6);
    else
      r =  201
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Medium_pi, Medium_pi);
}

#endif

