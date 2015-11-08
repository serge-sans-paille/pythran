//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_INVLOG_10_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_INVLOG_10_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Invlog_10 generic tag

      Represents the Invlog_10 constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Invlog_10, double
                                , 0, 0x3ede5bd9UL
                                , 0x3fdbcb7b1526e50dULL
                                )
  }
  /*!
    Generates constant 1/log(10).

    @par Semantic:

    @code
    T r = Invlog_10<T>();
    @endcode

    is similar to:

    @code
    r =  T(0.4342944819032518276511289189166050822943970058036666);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Invlog_10, Invlog_10);
}

#endif
