//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_INVEXP_1_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_INVEXP_1_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief Invexp_1 generic tag

     Represents the Invexp_1 constant in generic contexts.

     @par Models:
        Hierarchy
   */
    BOOST_SIMD_CONSTANT_REGISTER( Invexp_1, double
                                , 0, 0x3ebc5ab2
                                , 0x3fd78b56362cef38ll
                                )
  }
  /*!
    Generates constant 1/e.

    @par Semantic:
    The e constant is the real number such that \f$\log(e) = 1\f$.

    @code
    T r = Invexp_1<T>();
    @endcode

    is similar to:

    @code
    r =  T(0.3678794411714423215955237701614608674458111310317678);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Invexp_1, Invexp_1);
}

#endif
