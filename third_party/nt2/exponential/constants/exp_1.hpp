//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_EXP_1_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_EXP_1_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Exp_1 generic tag

      Represents the Exp_1 constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Exp_1, double
                                , 2, 0x402df854
                                , 0x4005bf0a8b145769LL
                                )
  }
  /*!
    Generates constant e.

    @par Semantic:
    The e constant is the real number such that \f$\log(e) = 1\f$

    @code
    T r = Exp_1<T>();
    @endcode

    is similar to:

    @code
      r =  T(2.71828182845904523536028747135266249775724709369995);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Exp_1, Exp_1);
}

#endif
