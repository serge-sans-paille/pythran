//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_FIFTEEN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_FIFTEEN_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Fifteen generic tag

     Represents the Fifteen constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Fifteen,double
                                , 15,0x41700000,0x402e000000000000ll
                                )
  }
  /*!
    Generates value 15 in the chosen type

    @par Semantic:

    @code
    T r = Fifteen<T>();
    @endcode

    is similar to:

    @code
    T r = T(15);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fifteen, Fifteen)
} }

#include <boost/simd/constant/common.hpp>

#endif
