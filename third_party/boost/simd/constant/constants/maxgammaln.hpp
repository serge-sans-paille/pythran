//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MAXGAMMALN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MAXGAMMALN_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Maxgammaln generic tag

     Represents the Maxgammaln constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Maxgammaln, double, 1
                                , 0x7bc3f8eaLL, 0x7f574c5dd06d2516ULL
                                );
  }
  /*!
    Generates value \f$\log\pi\f$

    @par Semantic:

    @code
    T r = Maxgammaln<T>();
    @endcode

    is similar to:

    @code
    if T is float
      T r = 2.035093e36f
    else if T is double
      T r = 2.556348e305
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Maxgammaln, Maxgammaln)
} }

#include <boost/simd/constant/common.hpp>

#endif
