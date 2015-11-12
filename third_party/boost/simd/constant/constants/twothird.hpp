//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_TWOTHIRD_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_TWOTHIRD_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Twothird generic tag

     Represents the Twothird constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Twothird, double, 0
                                , 0x3f2aaaabUL
                                , 0x3fe5555555555555ULL
                                )
  }
  /*!
    Generates value 2/3

    @par Semantic:

    @code
    T r = Twothird<T>();
    @endcode

    is similar to:

    @code
    T r = T(2)/T(3);
    @endcode

    @par Alias:

    Oneo_3
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Twothird, Twothird)
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Twothird, Twoo_3)
} }

#include <boost/simd/constant/common.hpp>

#endif
