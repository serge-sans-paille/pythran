//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_LOG2_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_LOG2_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief log2 generic tag

     Represents the log2 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct log2_ : ext::elementwise_<log2_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<log2_> parent;
    };
  }
  /*!
    base two logarithm function.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = log2(a0);
    @endcode

    is similar to:

    @code
    T0 r =  log(x)/log(Two<T0>());;
    @endcode

    @param a0

    @see @funcref{log10}, @funcref{log}, @funcref{log1p}
    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::log2_, log2, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::log2_, log2,(A0 const&)(A1&)(A2&),3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::log2_, log2,(A0 const&)(A1&),2)

}


#endif

