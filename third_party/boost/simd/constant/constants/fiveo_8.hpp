//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_FIVEO_8_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_FIVEO_8_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Fiveo_8 generic tag

     Represents the Fiveo_8 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Fiveo_8, double, 0
                                , 0x3f200000UL
                                , 0x3fe4000000000000ULL
                                )
  }
  /*!
    Generates value 5/8 = 0.625

    @par Semantic:

    @code
    T r = Fiveo_8<T>();
    @endcode

    is similar to:

    @code
    T r = T(5)/T(8);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fiveo_8, Fiveo_8)
} }

#include <boost/simd/constant/common.hpp>

#endif
