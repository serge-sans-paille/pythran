//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MLOGEPS2_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MLOGEPS2_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Mlogeps2 generic tag

     Represents the Mlogeps2 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Mlogeps2, double, 0
                                , 0x40FF1402, 0x403205966F2B4F13ULL
                                )
  }
  /*!
    Generates \f$-\log(eps^2)\f$ value

    @par Semantic:

    @code
    T r = Mlogeps2<T>();
    @endcode

    is similar to:

    @code
    T r = log(sqr(Eps<T>()));
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Mlogeps2, Mlogeps2)
} }

#include <boost/simd/constant/common.hpp>

#endif
