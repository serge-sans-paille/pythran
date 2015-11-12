//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_ONEOTWOEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_ONEOTWOEPS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Oneotwoeps generic tag

     Represents the Oneotwoeps constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER(Oneotwoeps,double,0
                                , 0X4A800000UL
                                , 0x4320000000000000ULL)
  }
  /*!
    Generates \f$1/(2\epsilon)\f$

    @par Semantic:

    @code
    T r = Oneotwoeps<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = T(0)
    else if T is double
      r =  pow(2.0, 52);
    else if T is float
      r =  pow(2.0f, 22);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Oneotwoeps, Oneotwoeps)
} }

#include <boost/simd/constant/common.hpp>

#endif
