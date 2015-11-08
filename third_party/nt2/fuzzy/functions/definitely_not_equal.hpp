//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_DEFINITELY_NOT_EQUAL_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_DEFINITELY_NOT_EQUAL_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief definitely_not_equal generic tag

     Represents the definitely_not_equal function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct definitely_not_equal_ : ext::elementwise_<definitely_not_equal_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<definitely_not_equal_> parent;
    };
  }
  /*!
    \f$ a0 \notin [a_1-\mathop{\mathrm{predecessor}}(a1,a_2),a_1-\mathop{\mathrm{successor}}(a1,a_2)]\f$

    @par Semantic:

    For every parameters of floating types respectively T0, T1, T2:

    @code
    T0 r = definitely_not_equal(a0,a1,a2);
    @endcode

    is similar to:

    @code
    T0 r = a1 >= successor(a0, n) || a1 <= predecessor(a0, n);
    @endcode

    see @funcref{predecessor}, @funcref{successor}
    @param a0

    @param a1

    @param a2

    @return a logical value  of the type associated the first parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::definitely_not_equal_, definitely_not_equal, 3)
}

#endif

