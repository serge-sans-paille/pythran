//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_NBD_ATAN2_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_NBD_ATAN2_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief nbd_atan2 generic tag

     Represents the nbd_atan2 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct nbd_atan2_ : ext::elementwise_<nbd_atan2_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<nbd_atan2_> parent;
    };
  }
  /*!
    nbd_atan2 function.
    The two-argument function nbd_atan2 is a variation of the @c atant2 function.
    BE WARNED
    nbd stands for "no bounds": atan2 is suposed to be faster than atan2 at the price that
    values for -inf, inf and nan are erroneous !

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 r = nbd_atan2(x,y);
    @endcode

    is similar to:

    @code
    T0 r = atan2(x,y);
    @endcode

    @see @funcref{atan2}, @funcref{atan}
    @param a0

    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::nbd_atan2_, nbd_atan2, 2)
}

#endif



