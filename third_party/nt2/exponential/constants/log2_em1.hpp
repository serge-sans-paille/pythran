//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_LOG2_EM1_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_LOG2_EM1_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief log2_em1 generic tag

      Represents the log2_em1 constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Log2_em1, double
                                , 0, 0x3ee2a8edUL
                                , 0x3fdc551d94ae0bf8ULL // 0.442695040888963e+00
                                )
  }
 /*!
    Generates constant Log2_em1. (\f$\log2(e)-1\f$)

    @par Semantic:

    @code
    T r = log2_em1<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Log2_em1, Log2_em1);
}

#endif
