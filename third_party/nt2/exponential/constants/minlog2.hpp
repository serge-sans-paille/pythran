//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_MINLOG2_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_MINLOG2_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Minlog2 generic tag

      Represents the Minlog2 constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Minlog2, double
                                , 0, 0xc2fe0000UL
                                , 0xc08ff00000000000ULL
                                )
  }
  /*!
    Generates constant Minlog2 used in logarithm/exponential computations

    @par Semantic:

    @code
    T r = Minlog2<T>();
    @endcode

    is similar to:

    @code
    if T is double
    r = -1023.0;
    else if T is float
    r = -127.0;

    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Minlog2, Minlog2);
}

#endif
