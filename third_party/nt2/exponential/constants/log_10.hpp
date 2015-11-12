//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_LOG_10_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_LOG_10_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Log_10 generic tag

      Represents the Log_10 constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Log_10, double
                                , 2, 0x40135d8eUL
                                , 0x40026bb1bbb55516ULL
                                )
  }
  /*!
    Generates constant Log_10. (\f$\log(10)\f$)

    @par Semantic:

    @code
    T r = Log_10<T>();
    @endcode

    is similar to:

    @code
      r =  T(2.302585092994045684017991454684364207601101488628773);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Log_10, Log_10);
}

#endif
