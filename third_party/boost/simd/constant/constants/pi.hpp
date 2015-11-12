//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_PI_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Pi generic tag

     Represents the Pi constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Pi, double, 3
                                , 0x40490FDB, 0x400921FB54442D18ULL
                                )
  }
  /*!
    Generates value \f$\pi\f$ that is the half length of a circle of radius one
    ... in normal temperature and pressure conditions.

    @par Semantic:

    @code
    T r = Pi<T>();
    @endcode

    is similar to:

    @code
    T r = T(4*atan(1));
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Pi, Pi)
} }

#include <boost/simd/constant/common.hpp>

#endif
