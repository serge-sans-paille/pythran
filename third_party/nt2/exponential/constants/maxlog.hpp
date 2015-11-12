//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_MAXLOG_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_MAXLOG_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Maxlog generic tag

      Represents the Maxlog constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Maxlog, double
                                , 0, 0x42b0c0a5UL
                                , 0x40862e42fefa39efULL
                                )
  }
  /*!
    Generates constant MaxLog used in logarithm/exponential computations
    nt2::log(x) return inf if x is greater than Maxlog (overflow)

    @par Semantic:

    @code
    T r = Maxlog<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = 709.78271289338400;
    else if T is float
      r =  88.3762626647949
    @endcode

    @see @{Minlog}

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Maxlog, Maxlog);
}

#endif
