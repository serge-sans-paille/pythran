//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_CORRECT_FMA_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_CORRECT_FMA_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  correct_fma generic tag

      Represents the correct_fma function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct correct_fma_ : ext::elementwise_<correct_fma_>
    {
     /// @brief Parent hierarchy
     typedef ext::elementwise_<correct_fma_> parent;
    };
  }
  /*!
    Computes fused multiply/add of its parameter.

    @par semantic:
    For any given value @c a, @c b, @c c of type @c T:

    @code
    T r = correct_fma(a, b, c);
    @endcode

    is similar to:

    @code
    T r = a*b+c;
    @endcode

    but with only one rounding

    @par Note:

    For integer a*b+c is performed

    For floating points numbers, always compute the correct fused multiply add,
    this means the computation of a0*a1+a2 with only one rounding operation.
    On machines not possessing this hard wired capability this can be very
    expansive.

    @c correct_fma is in fact a transitory function that allows to ensure
    strict fma capabilities,  i.e. only one rounding operation and no undue
    overflow in intermediate computations.

    If you are using this function for a system with no hard wired fma
    and are sure that overflow is not a problem
    you can define BOOST_SIMD_DONT_CARE_CORRECT_FMA_OVERFLOW to get better
    performances

    This function is never used internally in boost/simd. See also
    the @funcref{fma} function.

    @see  @funcref{fma}
    @param  a0

    @param  a1

    @param  a2

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::correct_fma_, correct_fma, 3)
} }

#endif
