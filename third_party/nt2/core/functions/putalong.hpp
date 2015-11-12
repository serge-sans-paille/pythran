//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_PUTALONG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_PUTALONG_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief putalong generic tag

     Represents the putalong function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct putalong_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /*!

    transform a0 in an expression "vector" in direction a1

    @par Semantic:

    For everytable expressions:

    @code
    T0 r = putalong(a0,a1);
    @endcode

    resize a0 to [1, ..., numel(a0)] where the size vector is of length a1

    @param a0

    @param a1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::putalong_, putalong, 2)
}

#endif
