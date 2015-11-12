//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_MAXLOG10_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_MAXLOG10_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Maxlog10 generic tag

      Represents the Maxlog10 constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Maxlog10, double
                                , 0, 0x4218ec59UL
                                , 0x40734413509f79feULL
                                )
  }
  /*!
    Generates constant Maxlog10 used in logarithm/exponential computations

    @par Semantic:

    @code
    T r = Maxlog10<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = 308.2547155599167;
    else if T is float
      r = 38.23080825805664;

    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Maxlog10, Maxlog10);
}

#endif
