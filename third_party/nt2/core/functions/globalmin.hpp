//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALMIN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALMIN_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the globalmjn functor
    **/
    struct globalmin_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }

  /*!
    @brief minimum  of all the elements of a table expression and its position.

    Computes minimum of all the elements of a table expression and optionaly its linear index

    @par Semantic

    For any table expression @c t and any arithmetic value @c p :

    @code
    T r = globalmin(t);
    @endcode

    is equivalent to:

    @code
    T r = min(a(_));
    @endcode

    and

    @code
    ptrdiff_t i;
    T m = globalmin(t, i);
    @endcode

    is equivalent to:

    @code
    T r = min(a(_));
    ptrdiff_t i =  globalfind(eq(a0, m))
    @endcode


    @see @funcref{colon}, @funcref{asump}, @funcref{globalfind}
    @param a0 Table to process
    @param a1  optional L-value to receive the index

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::globalmin_, globalmin,(A0 const&)(A1&),2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::globalmin_, g_min ,(A0 const&)(A1&),2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalmin_       , globalmin, 1)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalmin_       , g_min, 1)

}

#endif
