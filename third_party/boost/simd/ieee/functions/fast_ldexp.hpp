//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_FAST_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_FAST_LDEXP_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief fast_ldexp generic tag

     Represents the fast_ldexp function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fast_ldexp_ : ext::elementwise_<fast_ldexp_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_ldexp_> parent;
    };
  }
  /*!
    The function multiply a floating entry \f$a_0\f$
    by \f$2^{a_1}\f$

    @par Semantic:

    @code
    T r = fast_ldexp(a0,a1);
    @endcode

    is similar to:

    @code
    T r =  a0*pow(2, a1);
    @endcode

    @par Note:
    The fast prefix indicates that for speed sake
    the result may be incorrect for limiting values:
    inf, -inf nan and zero that deserve special treatment.If you are not sure use @funcref{ldexp}, at the expense
    of some more machine cycles.

    @see  @funcref{ldexp}
    @param a0

    @param a1

    @return a value of same type as the inputs
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_ldexp_, fast_ldexp, 2)
} }

#endif
