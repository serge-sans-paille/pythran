//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_TWOTOMNMBO_3_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_TWOTOMNMBO_3_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Twotomnmbo_3 generic tag

      Represents the Twotomnmbo_3 constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Twotomnmbo_3, double
                                , 0, 0x3ba14518LL
                                , 0x3ed428a2f98d7286ULL
                                )
  }
  /*!
    Generates constant e.

    @par Semantic:
    /f$2^(-nmb/3)/f$

    @code
    T r = twotomnmbo_3<T>();
    @endcode

    is similar to:

    @code
    if T is float
      r = 4.921566601151848e-03f
    else
      r = 4.806217383937348e-06
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Twotomnmbo_3, Twotomnmbo_3);
}

#endif
