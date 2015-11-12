//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_INVLOG_2_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_INVLOG_2_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Invlog_10 generic tag

      Represents the Invlog_10 constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Invlog_2, double
                                , 1, 0x3fb8aa3b
                                , 0x3ff71547652b82feLL
                                )
  }
  /*!
    Generates constant 1/log(2).

    @par Semantic:

    @code
    T r = Invlog_2<T>();
    @endcode

    is similar to:

    @code
     r =  T(1.442695040888963407359924681001892137426645954152986);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Invlog_2, Invlog_2);
}

#endif
