//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_TWOTO31_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_TWOTO31_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4310) // cast truncate constants
#endif


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Twoto31 generic tag

     Represents the Twoto31 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Twoto31, double, (1 << 31)
                                , 0x4f000000, 0x41e0000000000000LL
                                )
  }
  /*!
    Generates 2 to the power 31 (\f$2^{31}\f$)

    @par Semantic:

    @code
    T r = Twoto31<T>();
    @endcode

    is similar to:

    @code
    T r = pow(2, 31);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Twoto31, Twoto31)
} }

#include <boost/simd/constant/common.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
