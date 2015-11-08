//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_GREATESTNONINTEGER_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_GREATESTNONINTEGER_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Greatestnoninteger generic tag

     Represents the Greatestnoninteger constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Greatestnoninteger , double, 0
                                , 0x4affffffLL, 0x432fffffffffffffULL
                                );
  }
  /*!
    Generates the least integer value which is exactly
    representable in floating point numbers and
    equal to its integral successor.

    All floating numbers greater than Greatestnoninteger are integral.

    @par Semantic:

    @code
    T r = Greatestnoninteger<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = 4503599627370495.5
    else if T is float
      r = 8388607.5f
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Greatestnoninteger, Greatestnoninteger)
} }

#include <boost/simd/constant/common.hpp>

#endif
