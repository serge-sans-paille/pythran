//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_FACT_4_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_FACT_4_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Fact_4 generic tag

     Represents the Fact_4 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Fact_4,double
                                , 24, 0x41c00000, 0x4038000000000000ll
                                )
  }
  /*!
    Generates 4! that is 24

    @par Semantic:

    @code
    T r = Fact_4<T>();
    @endcode

    is similar to:

    @code
    T r = T(24);
    @endcode

    @par Alias

    Twentyfour

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fact_4, Fact_4)
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fact_4, Twentyfour)
} }

#include <boost/simd/constant/common.hpp>

#endif
