//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_ONEOSQRT5_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_ONEOSQRT5_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Oneosqrt5 generic tag

     Represents the Oneosqrt5 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER(Oneosqrt5,double,0
                                , 0x3ee4f92eUL
                                , 0x3fdc9f25c5bfedd9ULL);
  }
  /*!
    Generates \f$1/\sqrt5\f$

    @par Semantic:

    @code
    T r = Oneosqrt5<T>();
    @endcode

    is similar to:

    @code
      r =  1/sqrt(T(5));
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Oneosqrt5, Oneosqrt5)
} }

#include <boost/simd/constant/common.hpp>

#endif
