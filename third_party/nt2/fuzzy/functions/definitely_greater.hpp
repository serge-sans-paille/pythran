//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_DEFINITELY_GREATER_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_DEFINITELY_GREATER_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief definitely_greater generic tag

     Represents the definitely_greater function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct definitely_greater_ : ext::elementwise_<definitely_greater_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<definitely_greater_> parent;
    };
  }
  /*!
    \f$a_0 >  \mathop{\mbox{successor}}(a_1,a_2)\f$

    @par Semantic:

    For every parameters of floating types respectively T0, T1, T2:

    @code
    T0 r = definitely_greater(a0,a1,a2);
    @endcode

    is similar to:

    @code
    T0 r = a0 > successor(a1, n);
    @endcode

    @param a0

    @param a1

    @param a2

    @return a logical value  of the type associated the first parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::definitely_greater_, definitely_greater, 3)
}

#endif

