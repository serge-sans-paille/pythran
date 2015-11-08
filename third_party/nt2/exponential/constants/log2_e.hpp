//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_LOG2_E_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_LOG2_E_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief log2_e generic tag

      Represents the log2_e constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Log2_e, double
                                , 0, 0x3fb8aa3bUL
                                , 0x3fe62e42fefa39efULL // 1.442695040888963e+00
                                )
  }
 /*!
    Generates constant Log2_e.This constant is coupled with Log2_lo and is
    used in the float logarithms computations
    We have double(Log2_e<float>())+double(Log2_lo<float>()) == Log_2<double>()

    @par Semantic:

    @code
    T r = log2_e<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Log2_e, Log2_e);
}

#endif
