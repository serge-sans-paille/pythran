//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_ONEO_7_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_ONEO_7_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Oneo_7 generic tag

     Represents the Oneo_7 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Oneo_7, double, 0
                                 , 0x3e124925, 0x3fc2492492492492ll
                                )
  }
  /*!
    Generates value 1/7

    @par Semantic:

    @code
    T r = Oneo_7<T>();
    @endcode

    is similar to:

    @code
    T r = T(1)/T(7);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Oneo_7, Oneo_7)
} }

#include <boost/simd/constant/common.hpp>

#endif

