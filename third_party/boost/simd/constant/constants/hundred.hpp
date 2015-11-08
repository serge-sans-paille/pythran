//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_HUNDRED_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_HUNDRED_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Hundred generic tag

     Represents the Hundred constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Hundred,double
                                , 100, 0x42c80000, 0x4059000000000000ll
                                )
  }
  /*!
    Generates the value 100 in the chosen type

    @par Semantic:

    @code
    T r = Hundred<T>();
    @endcode

    is similar to

    @code
    T r = T(100);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Hundred, Hundred)
} }

#include <boost/simd/constant/common.hpp>

#endif
