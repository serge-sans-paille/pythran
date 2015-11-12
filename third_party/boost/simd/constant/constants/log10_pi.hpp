//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_LOG10_PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_LOG10_PI_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Log10_pi generic tag

     Represents the Log10_pi constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Log10_pi, double, 3
                                  , 0x3efe8a6e, 0x3fdfd14db31ba3bbll
                                  )
  }
  /*!
    Generates base ten logarithm of pi used in pispace (\f$\log(\pi)\f$)

    @par Semantic:

    @code
    T r = Log10_pi<T>();
    @endcode

    is similar to:

    @code
    T r = log10(Pi<T>());
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Log10_pi, Log10_pi)
} }

#include <boost/simd/constant/common.hpp>

#endif
