//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_MINLOG10_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_MINLOG10_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Minlog10 generic tag

      Represents the Minlog10 constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Minlog10, double
                                , 0, 0xc2179999UL
                                , 0xc0734413509f79feULL
                                )
  }
  /*!
    Generates constant Minlog10 used in logarithm/exponential computations

    @par Semantic:

    @code
    T r = Minlog10<T>();
    @endcode

    is similar to:

    @code
    if T is double
    r = -308.2547155599167;
    else if T is float
    r = -37.89999771118164;

    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Minlog10, Minlog10);
}

#endif
