//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_LDEXP_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief ldexp generic tag

     Represents the ldexp function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct ldexp_ : ext::elementwise_<ldexp_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ldexp_> parent;
    };
  }
  /*!
    The function multiply a floating entry \f$a_0\f$
    by \f$2^{a_1}\f$

    @par Semantic:

    @code
    T r = ldexp(a0,a1);
    @endcode

    is similar to:

    @code
    T r = a0*pow(2, a1);
    @endcode

    @param a0

    @param a1

    @return a value of same type as the inputs
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ldexp_, ldexp, 2)
} }

#endif
