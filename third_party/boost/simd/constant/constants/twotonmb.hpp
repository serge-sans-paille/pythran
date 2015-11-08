//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_TWOTONMB_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_TWOTONMB_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Twotonmb generic tag

     Represents the Twotonmb constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Twotonmb, double, 0
                                , 0x4B000000, 0x4330000000000000ULL
                                )
  }
  /*!
    Generates two to the number of mantissa bits.

    @par Semantic:

    @code
    T r = Twotonmb<T>();
    @endcode

    is similar to:

    @code
    T r = pow(2, Nbmantissabits<T>());
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Twotonmb, Twotonmb)
} }

#include <boost/simd/constant/common.hpp>

#endif
