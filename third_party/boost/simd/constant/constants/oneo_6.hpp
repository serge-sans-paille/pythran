//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_ONEO_6_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_ONEO_6_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Oneo_6 generic tag

     Represents the Oneo_6 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Oneo_6, double, 0
                                 , 0x3e2aaaab, 0x3fc5555555555555ll
                                )
  }
  /*!
    Generates value 1/6

    @par Semantic:

    @code
    T r = Oneo_6<T>();
    @endcode

    is similar to:

    @code
    T r = T(1)/T(6);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Oneo_6, Oneo_6)
} }

#include <boost/simd/constant/common.hpp>

#endif

