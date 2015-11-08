//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_LOG_2LO_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_LOG_2LO_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief log_2lo generic tag

      Represents the log_2lo constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Log_2lo, double
                                , 0, 0xb95e8083UL     //-0.00021219444f
                                , 0x3dea39ef35793c76ULL  //1.90821492927058770002e-10
                                )
  }
 /*!
    Generates constant Log_2lo.This constant is coupled with Log2_hi and is
    used in the float logarithms computations
    We have double(Log_2lo<float>())+double(Log2_hi<float>()) == Log_2<double>()

    @par Semantic:

    @code
    T r = log_2lo<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Log_2lo, Log_2lo);
}

#endif
