//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_CAURND_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_CAURND_HPP_INCLUDED

#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief caurnd generic tag

     Represents the caurnd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct caurnd_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /*!
    @brief cauchy pseudo random numbers generator : inverse cumulative method using rand

    @par Semantic:

    For every table expressions and  scalars m and s of type T0

    @code
    auto r = caurnd(m, s, <sizing parameters>);
    @endcode

    generates a table expression of random numbers following the cauchy distribution
    of median m, scale factor s and of size defined by the sizing parameters

    @code
    auto r = cauinv(rand(<sizing parameters>, as_<T0>(), m, s);
    @endcode

      - if as_<T0>() is not present the type of the generated elements is defined as
        being the type of m,

      - caurnd(as_<T0>()) by himself generates one value of type T0, assuming m = 0, s = 1,

      - caurnd() assumes T0 is double.

    @see @funcref{as_},  @funcref{rand},  @funcref{cauinv}
    @param a0 points of evaluation
    @param a1 optional median default to 0
    @param a2 optional scale default to 1
    @param a3
    @param a4
    @param a5
    @param a6

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 7)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 4)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 5)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 6)
}



#endif
