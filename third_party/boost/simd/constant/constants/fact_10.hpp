//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 20010 - 2011   LRI    UMR 10623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_FACT_10_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_FACT_10_HPP_INCLUDED

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
     @brief Fact_10 generic tag

     Represents the Fact_10 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Fact_10,double
                                , 3628800,0x4a5d7c00, 0x414baf8000000000ll
                                )
  }
  /*!
    Generates 10! that is 3628800

    @par Semantic:

    @code
    T r = Fact_10<T>();
    @endcode

    is similar to:

    @code
    T r = T(3628800);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fact_10, Fact_10)
} }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/simd/constant/common.hpp>

#endif
