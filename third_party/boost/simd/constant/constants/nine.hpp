//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_NINE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_NINE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Nine generic tag

     Represents the Nine constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Nine, double, 9
                                , 0x41100000UL, 0x4022000000000000ULL
                                )
  }
  /*!
    Generates value 9

    @par Semantic:

    @code
    T r = Nine<T>();
    @endcode

    is similar to:

    @code
    T r = T(9);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Nine, Nine)
} }

#include <boost/simd/constant/common.hpp>

#endif
