//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_TWOTOM10_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_TWOTOM10_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Twotom10 generic tag

     Represents the Twotom10 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Twotom10, double, 0
                                , 0x3A800000, 0x3F50000000000000ULL
                                )
  }
  /*!
    Generates 2 to the power -10 (\f$2^{-10}\f$)

    @par Semantic:

    @code
    T r = Twotom10<T>();
    @endcode

    is similar to:

    @code
    T r = pow(2, -10);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Twotom10, Twotom10)
} }

#include <boost/simd/constant/common.hpp>

#endif
