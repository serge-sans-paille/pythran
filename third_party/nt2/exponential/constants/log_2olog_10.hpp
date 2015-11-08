//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_LOG_2OLOG_10_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_LOG_2OLOG_10_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Log_2olog_10 generic tag

      Represents the Log_2olog_10 constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Log_2olog_10, double
                                , 0, 0x3e9a209bUL
                                , 0x3fd34413509f79ffULL
                                )
  }
  /*!
    Generates constant Log_2olog_10.  (\f$\frac{\log(2)}{\log(10)}\f$)

    @par Semantic:

    @code
    T r = Log_2olog_10<T>();
    @endcode

    is similar to:

    @code
      r =  T(0.3010299956639811952137388947244930267681898814621085);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Log_2olog_10, Log_2olog_10);
}

#endif
