//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_HALF_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_HALF_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Half generic tag

     Represents the Half constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER(Half,double,0,0x3F000000,0x3FE0000000000000ULL)
  }
  /*!
    Generates value \f$\frac12\f$

    @par Semantic:

    @code
    T r = Half<T>();
    @endcode

    is similar for floating types to:

    @code
    T r = T(1)/T(2);
    @endcode

    and returns 0 for integral types

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Half, Half)
} }

#include <boost/simd/constant/common.hpp>

#endif
