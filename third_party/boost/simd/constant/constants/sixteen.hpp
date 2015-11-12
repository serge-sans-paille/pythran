//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SIXTEEN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SIXTEEN_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Sixteen generic tag

     Represents the Sixteen constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Sixteen, double, 16
                                , 0x41800000UL, 0x4030000000000000ULL
                                )
  }
  /*!
    Generates value 6

    @par Semantic:

    @code
    T r = Sixteen<T>();
    @endcode

    is similar to:

    @code
    T r = T(6);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Sixteen, Sixteen)
} }

#include <boost/simd/constant/common.hpp>

#endif
