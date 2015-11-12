//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SQRTSMALLESTPOSVAL_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SQRTSMALLESTPOSVAL_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Sqrtsmallestposval generic tag

     Represents the Sqrtsmallestposval constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Sqrtsmallestposval , double, 1
                                , 0x20000000, 0x2000000000000000ll
                                )
  }
  /*!
    Generates the square root of the least non zero positive
    value of the chosen type.

    @par Semantic:

    @code
    T r = Sqrtsmallestposval<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 1
    else if T is double
      r =  1.491668146240041e-154;
    else if T is float
      r =   1.0842022e-19;
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Sqrtsmallestposval, Sqrtsmallestposval)
} }

#include <boost/simd/constant/common.hpp>

#endif
