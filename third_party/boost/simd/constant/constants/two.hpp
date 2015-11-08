//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_TWO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_TWO_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Two generic tag

     Represents the Two constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Two, double, 2
                                , 0x40000000UL, 0x4000000000000000ULL
                                )
  }
  /*!
    Generates value 2

    @par Semantic:

    @code
    T r = Two<T>();
    @endcode

    is similar to:

    @code
    T r = T(2);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Two, Two)
} }

#include <boost/simd/constant/common.hpp>

#endif
