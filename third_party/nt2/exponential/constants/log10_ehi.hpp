//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_LOG10_EHI_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_LOG10_EHI_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief log10_ehi generic tag

      Represents the log10_ehi constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Log10_ehi, double
                                , 0, 0x3ede0000UL       // 4.3359375E-1f
                                , 0x3fdbcb7b1526e510ULL // 0.442695040888963e+00
                                )
  }
 /*!
    Generates constant log10_ehi.This constant is coupled with Log10_elo and is
    used in the float logarithms computations
    We have double(log10_ehi<float>())+double(Log10_elo<float>()) == Log_10(e)

    @par Semantic:

    @code
    T r = log10_ehi<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Log10_ehi, Log10_ehi);
}

#endif
