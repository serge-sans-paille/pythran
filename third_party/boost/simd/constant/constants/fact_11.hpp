//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 20011 - 2011   LRI    UMR 11623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_FACT_11_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_FACT_11_HPP_INCLUDED

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
     @brief Fact_11 generic tag

     Represents the Fact_11 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Fact_11,double
                                , 39916800,0x4c184540,0x418308a800000000ll
                                )
  }
  /*!
    Generates 11! that is 39916800,

    @par Semantic:

    @code
    T r = Fact_11<T>();
    @endcode
    is similar to:

    @code
    T r = T(39916800);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fact_11, Fact_11)
} }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/simd/constant/common.hpp>

#endif
