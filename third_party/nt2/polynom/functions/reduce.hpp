//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_REDUCE_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_REDUCE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief reduce generic tag

     Represents the reduce function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct reduce_ : ext::elementwise_<reduce_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<reduce_> parent;
    };
  }
  /*!
    returns the same polynomial as the input insuring
    that the first element of the polynomial is non zero (or the
    polynomial is empty)


    @par Semantic:

    For every polynomial p

    @code
    auto r = reduce(p);
    @endcode

    @param a0

    @return a polynomial expression
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::reduce_,reduce, 1)
  /*!
    returns the same polynomial as the input insuring
    that the first element of the polynomial is non zero (or the
    polynomial is empty)

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = reduce(p, tol);
    @endcode

    The second parameter is a relative threshold on what can be considered as zero
    (neglectable) or an overflow threshold _ that consider that iteratively from
    first index p(i) is neglectable if any p(j)/pi() is infinite.

    @param a0
    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::reduce_,reduce, 2)
}
#endif
