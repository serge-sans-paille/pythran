//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_LOG10_2LO_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_LOG10_2LO_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief log10_2lo generic tag

      Represents the log10_2lo constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Log10_2lo, double
                                , 0, 0x39826a14UL  //2.4874569E-4f
                                , 0x3ed3509f79fef312ULL // 0.000004605038981195214
                                )
  }
 /*!
    Generates constant log10_2lo.This constant is coupled with Log10_2hi and is
    used in the float logarithms computations
    We have abs( double(log10_2lo<float>())+double(Log10_2hi<float>()) - Log10(2.0))) < 3e-11

    @par Semantic:

    @code
    T r = log10_2lo<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Log10_2lo, Log10_2lo);
}

#endif
