//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_POWLOWLIM_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_POWLOWLIM_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief powlowlim generic tag

      Represents the powlowlim constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Powlowlim, double
                                , 0, 0xc5160000UL //-2400
                                , 0xc0d0c7c000000000ULL //-17183
                                )
  }
 /*!
    Generates constant powlowlim

    @par Semantic:

    @code
    T r = powlowlim<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Powlowlim, Powlowlim);
}

#endif
