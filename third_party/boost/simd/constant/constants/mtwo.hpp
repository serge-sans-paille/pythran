//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MTWO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MTWO_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Mtwo generic tag

     Represents the Mtwo constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Mtwo, double, -2
                                , 0xc0000000UL, 0xc000000000000000ULL
                                )
  }
  /*!
    Generates value = -2

    @par Semantic:

    @code
    T r = Mtwo<T>();
    @endcode

    is similar to:

    @code
    T r = T(-2);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Mtwo, Mtwo)
} }
#include <boost/simd/constant/common.hpp>

#endif

