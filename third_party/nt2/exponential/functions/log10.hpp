//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_LOG10_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_LOG10_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief log10 generic tag

     Represents the log10 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct log10_ : ext::elementwise_<log10_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<log10_> parent;
    };
  }
  /*!
    base ten logarithm function. For integer input types log10 return the truncation
    of the real result.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = log10(x);
    @endcode

    is similar to:

    @code
    T0 r = log(x)/log(Ten<T0>());
    @endcode

    @see @funcref{log}, @funcref{log2}, @funcref{log1p}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::log10_, log10, 1)
}

#endif

