//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_MAXLOG2_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_MAXLOG2_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Maxlog2 generic tag

      Represents the Maxlog2 constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Maxlog2, double
                                , 0, 0x42fe0000UL
                                , 0x408ff80000000000ULL
                                )
  }
  /*!
    Generates constant Maxlog2 used in logarithm/exponential computations

    @par Semantic:

    @code
    T r = Maxlog2<T>();
    @endcode

    is similar to:

    @code
    if T is double
    r = 1023.0;
    else if T is float
    r = 127.0;

    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Maxlog2, Maxlog2);
}

#endif
