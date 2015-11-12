//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_TOLERANT_TRUNC_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_TOLERANT_TRUNC_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief tolerant_trunc generic tag

     Represents the tolerant_trunc function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct tolerant_trunc_ : ext::elementwise_<tolerant_trunc_> { typedef ext::elementwise_<tolerant_trunc_> parent; };
  }
  /*!
    Computes the truncation with a tolerance of 3 ulps using Hagerty's FL5 function.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = tolerant_trunc(a0);
    @endcode

    is similar to:

    @code
    T0 r;
    T0 xp =  pred(x);
    T0 xc =  succ(x);
    if (is_flint(prev(x))) r = pred(x);
    else if is_flint(next(x)) r = next(x);
    else r = trunc(x);
    @endcode

    @par Note:
    See Knuth, Art Of Computer Programming, Vol. 1, Problem 1.2.4-5.

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::tolerant_trunc_, tolerant_trunc, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::tolerant_trunc_, ttrunc, 1)
}

#endif

