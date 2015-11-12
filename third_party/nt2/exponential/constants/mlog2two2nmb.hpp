//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_MLOG2TWO2NMB_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_MLOG2TWO2NMB_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Mlog2two2nmb generic tag

      Represents the Mlog2two2nmb constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Mlog2two2nmb, double
                                , 0, 0xc1b80000UL
                                , 0xc04a800000000000ULL
                                )
  }
 /*!
    Generates constant Mlog2two2nmb.

    @par Semantic:

    @code
    T r = Mlog2two2nmb<T>();
    @endcode

    is similar to:

    @code
      r =  T(Nbmantissabits<T>());
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Mlog2two2nmb, Mlog2two2nmb);
}

#endif
