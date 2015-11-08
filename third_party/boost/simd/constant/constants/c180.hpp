//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_C180_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_C180_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief C180 generic tag

     Represents the C180 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( C180, double, 0
                                 , 0x43340000, 0x4066800000000000ll
                                )
  }
  /*!
    Generates the value 180 in the chosen type

    @par Semantic:

    @code
    T r = C180<T>();
    @endcode

    is similar to

    @code
    T r = T(180);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::C180, C180)
} }

#include <boost/simd/constant/common.hpp>

#endif

