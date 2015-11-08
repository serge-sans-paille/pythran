//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIGNGAM_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIGNGAM_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief signgam generic tag

     Represents the signgam function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct signgam_ : ext::elementwise_<signgam_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<signgam_> parent;
    };
  }
  /*!
    sign of gamma function

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = signgam(x);
    @endcode

    is similar to

    @code
    T0 r = sign(gamma(x));
    @endcode

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::signgam_, signgam, 1)
}

#endif

