//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_RAT_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_RAT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief rat generic tag

     Represents the rat function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct rat_ : ext::elementwise_<rat_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<rat_> parent;
    };
  }
  /*!
    rational approximation of floating numbers

    @par Semantic:

    For every table expression

    @code
    tie(n, d) = rat(a0, tol);
    @endcode

    returns n and d such that (whenever possible) n/d
    represents n within a tolerance of tol

    @param a0
    @param a1

    @return an expression which eventually will evaluate to the result
  **/
    NT2_FUNCTION_IMPLEMENTATION(tag::rat_, rat, 2)
    /// @overload
    NT2_FUNCTION_IMPLEMENTATION(tag::rat_, rat, 1)
    /// @overload
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rat_, rat,(A0 const&)(A1 const&)(A2&)(A3&),4)
    /// @overload
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rat_, rat,(A0 const&)(A1&)(A2&),3)
}

#endif

