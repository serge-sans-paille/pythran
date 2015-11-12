//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_YNI_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_YNI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief yni generic tag

     Represents the yni function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct yni_ : ext::elementwise_<yni_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<yni_> parent;
    };
  }
  /*!
    Modified Bessel function of the first kind of order n.

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = yni(a0,a1);
    @endcode

    Computes \f$\displaystyle \lim_{\nu \rightarrow n} \frac{\cos(\nu\pi)J_{\nu}(x)-J_{-\nu}(x)}{\cos(\nu\pi)}\f$

    @param a0

    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::yni_, yni, 2)
}

#endif

