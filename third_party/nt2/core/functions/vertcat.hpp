//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_VERTCAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_VERTCAT_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief vertcat generic tag

     Represents the vertcat function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct  vertcat_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /*!
    Vertical concatenation

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = vertcat(a0);
    @endcode

    is similar to:

    @code
    auto r = cat(1, a0, a1);
    @endcode

    @see @funcref{horzcat}, @funcref{cat}

    @par alias: @c catv
    @param a0
    @param a1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::vertcat_, vertcat, 2)
  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::vertcat_, vertcat, 1)
  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::vertcat_, catv, 1)
  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::vertcat_, catv, 2)
}

#endif
