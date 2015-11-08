//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_CONSTANTS_PI2O_6_HPP_INCLUDED
#define NT2_EULER_CONSTANTS_PI2O_6_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/config.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4310) // truncation of constant
#endif

namespace nt2
{
  namespace tag
  {
   /*!
     @brief Pi2o_6 generic tag

     Represents the Pi2o_6 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Pi2o_6, double
                                , 2, 0x3fd28d33LL
                                , 0x3ffa51a6625307d3ULL
                                )
  }
  /*!
    Generates \f$ \pi^2/6\f$

    @par Semantic:

    @code
    T r = Pi2o_6<T>();
    @endcode

    is similar to:

    @code
    T r =  sqr(Pi<T>())/Six<T>();
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pi2o_6, Pi2o_6);
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/simd/constant/common.hpp>

#endif
