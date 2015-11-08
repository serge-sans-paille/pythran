//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 20012 - 2012   LRI    UMR 12623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_FACT_12_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_FACT_12_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/config.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4310) // truncation of constant
#endif


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Fact_12 generic tag

     Represents the Fact_12 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Fact_12,double
                                , 479001600,0x4de467e0, 0x41bc8cfc00000000ll
                                )
  }
  /*!
    Generates 12! that is 479001600

    @par Semantic:

    @code
    T r = Fact_12<T>();
    @endcode

    is similar to:

    @code
    T r = T(479001600);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fact_12, Fact_12)
} }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/simd/constant/common.hpp>

#endif
