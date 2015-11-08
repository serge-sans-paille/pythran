//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_DAWSON_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_DAWSON_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief dawson generic tag

     Represents the dawson function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct dawson_ : ext::elementwise_<dawson_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<dawson_> parent;
    };
  }
  /*!
    Computes Dawson function

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = dawson(a0);
    @endcode

    Computes  \f$ D(a_0)=e^{-x^2}\int_0^{a_0} e^{t^2} \mbox{d}t\f$

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::dawson_, dawson, 1)
}

#endif

