//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MANTISSAMASK_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MANTISSAMASK_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Mantissamask generic tag

     Represents the Mantissamask constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Mantissamask,double
                                , 0,0x807FFFFFUL,0x800FFFFFFFFFFFFFULL
                                )
  }
  /*!
    Generates a mask used to compute the mantissa of a floating point value

    @par Semantic:

    @code
    as_integer<T> r = Mantissamask<T>();
    @endcode

    @code
    if T is double
      r =  -2.225073858507200889e-308;
    else if T is float
      r =  -1.1754942106924410755e-38;
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Mantissamask, Mantissamask)
} }

#include <boost/simd/constant/common.hpp>

#endif
