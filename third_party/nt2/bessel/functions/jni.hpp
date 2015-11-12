//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_JNI_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_JNI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief jni generic tag

     Represents the jni function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct jni_ : ext::elementwise_<jni_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<jni_> parent;
    };
  }
  /*!
    Bessel function of the first kind of order n.

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = jni(x,n);
    @endcode

    Computes \f$\displaystyle \frac1{\pi} \int_0^\pi \cos(x \sin t - n t)\mbox{d}t\f$

    @param a0

    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::jni_, jni, 2)
}

#endif

