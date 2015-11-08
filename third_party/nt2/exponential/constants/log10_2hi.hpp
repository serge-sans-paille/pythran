//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_LOG10_2HI_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_LOG10_2HI_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief log10_2hi generic tag

      Represents the log10_2hi constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Log10_2hi, double
                                , 0, 0x3e9a0000UL // 3.0078125E-1f
                                , 0x3fd3440000000000ULL // 0.301025390625
                                )
  }
 /*!
    Generates constant log10_2hi.This constant is coupled with Log10_2lo and is
    used in the float logarithms computations
    We have abs( double(log10_2hi<float>())+double(Log10_2lo<float>()) - Log10(2.0) < 3e-11

    @par Semantic:

    @code
    T r = log10_2hi<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Log10_2hi, Log10_2hi);
}

#endif
