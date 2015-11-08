//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_REALLOG_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_REALLOG_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief reallog generic tag

     Represents the reallog function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct reallog_ : ext::elementwise_<reallog_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<reallog_> parent;
    };
  }
  /*!
    Returns natural logarithm function,  but
    asserts if called with non real positive values.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = reallog(a0);
    @endcode

    is similar to:

    @code
    T0 r = log(a0);
    @endcode

    @see @funcref{log}

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::reallog_, reallog, 1)
}

#endif
