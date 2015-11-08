//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SQRTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SQRTEPS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Sqrteps generic tag

     Represents the Sqrteps constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Sqrteps, double, 1
                                , 0x39B504F3, 0x3E50000000000000ULL
                                )
  }
  /*!
    Generate square root of constant Eps
    square root of constant Eps

    @par Semantic:

    @code
    T r = Sqrteps<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 1
    else if T is double
      r =  Pow(2,-26);
    else if T is float
      r =  pow(2,-11.5f);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Sqrteps, Sqrteps)
} }

#include <boost/simd/constant/common.hpp>

#endif
