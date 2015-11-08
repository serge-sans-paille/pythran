//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_CONV_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_CONV_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2 {  namespace tag
  {
   /*!
     @brief conv generic tag

     Represents the conv function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct conv_ : ext::unspecified_<conv_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<conv_>  parent;
    };
  }
  /*!

    Polynomials multiplication and vectors convolution

    @par Semantic:

    For every expressions a,  b representing a polynomial:

    @code
    auto r = conv(a, b, shape);
    @endcode

    convolves vectors a and b.


    c = conv(a, b, shape) returns a subvector of the convolution with size
    specified by shape:
      - 'f'  (default) returns the 'full' convolution,
      - 's'  returns the central part of the convolution that is the 'same' size as a.
      - 'v'  returns only those 'valid' parts of the convolution that are computed without the zero-padded edges.

    If a and b are vectors representing polynomial coefficients, convolving them is almost
    equivalent to multiplying the two polynoms.
    @see @funcref{numel}

    @param a0

    @param a1

    @return returns an expression
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::conv_, conv, 2)

}

#endif
