//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_FACT_5_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_FACT_5_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Fact_5 generic tag

     Represents the Fact_5 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Fact_5,double
                                , 120, 0x42f00000,0x405e000000000000ll
                                )
  }
  /*!
    Generates 5!,  that is 120

    @par Semantic:

    @code
    T r = Fact_5<T>();
    @endcode

    is similar to:

    @code
    T r = T(120);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fact_5, Fact_5)
} }

#include <boost/simd/constant/common.hpp>

#endif
