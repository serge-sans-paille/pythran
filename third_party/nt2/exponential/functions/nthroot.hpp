//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_NTHROOT_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_NTHROOT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief nthroot generic tag

     Represents the nthroot function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct nthroot_ : ext::elementwise_<nthroot_>
    {
      /// @brief Parent hierarchy
       typedef ext::elementwise_<nthroot_> parent;
    };
  }
  /*!
    nth root function: \f$\sqrt[a_1]{a_0}\f$
    \arg a1 must be of integer type
    \arg if a1 is even and a0 negative the result is nan
    \arg if a0 is null the result is zero
    \arg if a0 is one  the result is one

    @par Semantic:

    For every parameters of  floating type T0 and integral type T1:
    nthroot is more expansive than pow(a0, rec(tofloat(a1))) because
    it takes care of some limits issues that pow does not mind of.
    See if it suits you better.

    @code
    T0 r = nthroot(x, n);
    @endcode

    is similar to:

    @code
    T0 r = n >= 0 ? pow(x, rec(T0(n))) : nan;
    @endcode


    @see @funcref{pow}, @funcref{rec}, @funcref{sqrt}, @funcref{cbrt}
    @param a0  must be of floating type

    @param a1  must be of integral type.

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::nthroot_, nthroot, 2)
}

#endif

