//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MAXFLINT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MAXFLINT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Maxflint generic tag

     Represents the Maxflint constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Maxflint , double, 1
                                , 0x4b800000, 0x4340000000000000ll
                                )
  }
  /*!
    Generates the least integer value which is exactly
    representable in floating point numbers and
    equal to its integral successor.

    All floating numbers greater than Maxflint are integral.

    @par Semantic:

    @code
    T r = Maxflint<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = 9007199254740992.0
    else if T is float
      r = 16777216.0f
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Maxflint, Maxflint)
} }

#include <boost/simd/constant/common.hpp>

#endif
