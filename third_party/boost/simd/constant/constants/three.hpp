//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_THREE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_THREE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Three generic tag

     Represents the Three constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Three, double, 3
                                , 0x40400000UL, 0x4008000000000000ULL
                                )
  }
  /*!
    Generates value 3

    @par Semantic:

    @code
    T r = Three<T>();
    @endcode

    is similar to:

    @code
    T r = T(3);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Three, Three)
} }

#include <boost/simd/constant/common.hpp>

#endif
