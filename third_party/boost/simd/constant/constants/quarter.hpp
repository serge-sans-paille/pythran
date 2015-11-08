//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_QUARTER_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_QUARTER_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Quarter generic tag

     Represents the Quarter constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Quarter, double, 0
                                , 0x3E800000, 0x3FD0000000000000ULL
                                )
  }
  /*!
    Generate value 1/4

    @par Semantic:

    @code
    T r = Quarter<T>();
    @endcode

    is similar to:

    @code
    T r = T(1)/T(4);
    @endcode

    @par Alias

    Oneo_4
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Quarter, Quarter)
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Quarter, Oneo_4)
} }

#include <boost/simd/constant/common.hpp>

#endif
