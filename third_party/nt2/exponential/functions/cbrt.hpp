//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_CBRT_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_CBRT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief cbrt generic tag

     Represents the cbrt function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct cbrt_ : ext::elementwise_<cbrt_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<cbrt_> parent;
    };
  }
  /*!
    Compute the cubic root: \f$\sqrt[3]{x}\f$

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = cbrt(x);
    @endcode

    is similar to:

    @code
    T0 r = pow(x, T0(1/3.0));
    @endcode

    @see @funcref{pow}, @funcref{boost::simd::sqrt}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cbrt_, cbrt, 1)
}

#endif

