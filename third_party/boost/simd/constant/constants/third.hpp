//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_THIRD_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_THIRD_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Third generic tag

     Represents the Third constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Third, double, 0
                                , 0x3EAAAAAB, 0x3FD5555555555555ULL
                                )
  }
  /*!
    Generates value 1/3

    @par Semantic:

    @code
    T r = Third<T>();
    @endcode

    is similar to:

    @code
    T r = T(1)/T(3);
    @endcode

    @par Alias:

    Oneo_3
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Third, Third)
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Third, Oneo_3)
} }

#include <boost/simd/constant/common.hpp>

#endif
