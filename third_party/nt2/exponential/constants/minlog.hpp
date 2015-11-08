//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_MINLOG_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_MINLOG_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Minlog generic tag

      Represents the Minlog constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Minlog, double
                                , 0, 0xc2b0c0a5UL
                                , 0xc086232bdd7abcd2ULL
                                )
  }
  /*!
    Generates constant Minlog used in logarithm/exponential computations
    nt2::log(x) return  0 if x is less than Minlog (underflow)

    @par Semantic:

    @code
    T r = Minlog<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = -708.3964185322641;
    else if T is float
      r = -88.3762626647949
    @endcode

    @see @{Maxlog}

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Minlog, Minlog);
}

#endif
