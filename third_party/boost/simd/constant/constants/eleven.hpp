//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_ELEVEN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_ELEVEN_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Eleven generic tag

     Represents the Eleven constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Eleven, double, 11
                                ,0x41300000,0x4026000000000000ll
                                )
  }
  /*!
     Generates the value 11

    @par Semantic:

    @code
    T r = Eleven<T>();
    @endcode

    is similar to:

    @code
    T r = T(11);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Eleven, Eleven)
} }

#include <boost/simd/constant/common.hpp>

#endif
