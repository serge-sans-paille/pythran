//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SIX_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SIX_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Six generic tag

     Represents the Six constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Six, double, 6
                                , 0x40c00000UL, 0x4018000000000000ULL
                                )
  }
  /*!
    Generates value 6

    @par Semantic:

    @code
    T r = Six<T>();
    @endcode

    is similar to:

    @code
    T r = T(6);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Six, Six)
} }

#include <boost/simd/constant/common.hpp>

#endif
