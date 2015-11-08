//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_FACT_8_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_FACT_8_HPP_INCLUDED

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
     @brief Fact_8 generic tag

     Represents the Fact_8 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Fact_8,double
                                , 40320,0x471d8000,0x40e3b00000000000ll
                                )
  }
  /*!
    Generates  8! that is 40320

    @par Semantic:

    @code
    T r = Fact_8<T>();
    @endcode

    is similar to:

    @code
    T r = T(40320);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fact_8, Fact_8)
} }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/simd/constant/common.hpp>

#endif
