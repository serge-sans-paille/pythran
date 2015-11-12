//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_NEGS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_NEGS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd {
  namespace tag
  {
    /*!
      @brief  negs generic tag

      Represents the negs function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct negs_ : ext::elementwise_<negs_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<negs_> parent;
    };
  }
  /*!
    Computes the saturated negation of the input.

    @par semantic:
    For any given value @c x, @c y of type @c T:

    @code
    T r = negs(x);
    @endcode

    The code is equivalent to:

    @code
    T r = -x
    @endcode

    @par Note:
    For integers types @c negs(Valmin) returns @c Valmax.

    @c negs is not defined for unsigned types.

    @par Alias

    saturated_neg

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::negs_, negs, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::negs_, saturated_neg, 1)
} }

#endif
