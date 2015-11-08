//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_LOG_2HI_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_LOG_2HI_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief log_2hi generic tag

      Represents the log_2hi constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Log_2hi, double
                                , 0, 0x3f318000UL        //0.693359375f
                                , 0x3fe62e42fee00000ULL  //6.93147180369123816490e-01
                                )
  }
 /*!
    Generates constant Log_2hi.This constant is coupled with Log2_lo and is
    used in the float logarithms computations
    We have double(Log_2hi<float>())+double(Log2_lo<float>()) == Log_2<double>()

    @par Semantic:

    @code
    T r = log_2hi<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Log_2hi, Log_2hi);
}

#endif
