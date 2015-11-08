//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_LOG10_ELO_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_LOG10_ELO_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief log10_elo generic tag

      Represents the log10_elo constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Log10_elo, double
                                , 0, 0x3a37b152UL  // 7.0073188e-04
                                , 0x0ULL
                                )
  }
 /*!
    Generates constant log10_elo.This constant is coupled with Log10_ehi and is
    used in the float logarithms computations
    We have abs( double(log10_elo<float>())+double(Log10_ehi<float>()) - Log_10(e)) < 3e-11

    @par Semantic:

    @code
    T r = log10_elo<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Log10_elo, Log10_elo);
}

#endif
