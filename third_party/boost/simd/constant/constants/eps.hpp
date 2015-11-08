//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_EPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_EPS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Eps generic tag

     Represents the Eps constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER(Eps,double,1,0X34000000,0x3CB0000000000000ULL)
  }
  /*!
    Generates two times the machine epsilon.

    @par Semantic:

    @code
    T r = Eps<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = T(1)
    else if T is double
      r =  pow(2.0, -53);
    else if T is float
      r =  pow(2.0f, -23);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Eps, Eps)
} }

#include <boost/simd/constant/common.hpp>

#endif
