//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_FIVE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_FIVE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Five generic tag

     Represents the Five constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Five,double
                                , 5,0x40a00000UL,0x4014000000000000ULL
                                )
  }
  /*!
     Generates value 5 in the chosen type

    @par Semantic:

    @code
    T r = Five<T>();
    @endcode

    is similar to:

    @code
    T r = T(5);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Five, Five)
} }

#include <boost/simd/constant/common.hpp>

#endif
