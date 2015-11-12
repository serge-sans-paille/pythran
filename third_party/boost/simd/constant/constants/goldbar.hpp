//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_GOLDBAR_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_GOLDBAR_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Goldbar generic tag

     Represents the Goldbar constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Goldbar,double,1
                                , 0xbf1e377aLL, 0xbfe3c6ef372fe950ULL
                                );
  }
  /*!
    Generates the goldbaren ratio that is \f$\phi = \frac{1+\sqrt5}{2}\f$

    @par Semantic:

    @code
    T r = Goldbar<T>();
    @endcode

    is similar for floating types to:

    @code
    T r = (1-sqrt(5))/2;
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Goldbar, Goldbar)
} }

#include <boost/simd/constant/common.hpp>

#endif
