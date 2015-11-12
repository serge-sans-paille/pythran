//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_LOGSQRT2PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_LOGSQRT2PI_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Logsqrt2pi generic tag

     Represents the Logsqrt2pi constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Logsqrt2pi, double, 0
                                , 0x3f6b3f8eLL, 0x3fed67f1c864beb5ULL // 0.91893853320467274178032973640562
                                );
  }
  /*!
    Generates value \f$\log\sqrt{2\pi}\f$

    @par Semantic:

    @code
    T r = Logsqrt2pi<T>();
    @endcode

    is similar to:

    @code
    T r = log(sqrt(2*Pi<T>());
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Logsqrt2pi, Logsqrt2pi)
} }

#include <boost/simd/constant/common.hpp>

#endif
