//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_UNIFRND_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_UNIFRND_HPP_INCLUDED

#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief unifrnd generic tag

     Represents the unifrnd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct unifrnd_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    uniform pseudo random numbers generator

    @par Semantic:

    For every table expressions and  scalars a and b of type T0

    @code
    auto r = unifrnd(a, b, <sizing parameters>);
    @endcode

    generates a table expression of random numbers following the uniform distribution
    on interval [a, b[ and of size defined by the sizing parameters

    @code
    auto r = (b-a)*rand(<sizing parameters>, as_<T0>())+a;
    @endcode

      - if as_<T0>() is not present the type of the generated elements is defined as
        being the type of a,

      - unifrnd(as_<T0>()) by himself generates one value of type T0, assuming a = 0, b = 1,

      - unifrnd() assumes T0 is double.

    @see @funcref{as_},  @funcref{rand}
    @param a0 points of evaluation
    @param a1
    @param a2
    @param a3
    @param a4
    @param a5
    @param a6

    @return an expression which eventually will evaluate to the result
  **/
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::unifrnd_, unifrnd, 7)
  /// @overload
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::unifrnd_, unifrnd, 2)
  /// @overload
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::unifrnd_, unifrnd, 3)
  /// @overload
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::unifrnd_, unifrnd, 4)
  /// @overload
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::unifrnd_, unifrnd, 5)
  /// @overload
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::unifrnd_, unifrnd, 6)
}

#endif
