//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MNORM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MNORM_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <boost/mpl/int.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/tags.hpp>

namespace nt2 { namespace tag
  {
    /*!
     @brief globalnorm generic tag

      Represents the mnorm function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct mnorm_ :  tag::formal_
    {
      /// INTERNAL ONLY
      typedef  boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Matricial norm

    Computes the matricial norms of a matrix expression with static or dynamic choice from
    by the optional second parameter
    that can be 1, nt2::tag::one_  2, nt2::two_, , nt2::inf_ or , nt2::fro_
    or the template parameter
    that can be 1, nt2::tag::one_  2, nt2::tag::two_, , nt2::tag::inf_ or , nt2::tag::fro_

    Call protocols to mnorm are summarized in the following table. We advise to use static
    calls whenever possible as it prevents cascaded run-time if clauses and goes directly
    to the right call at execution.

    @code
    |-------------------|-------------------|------------------------------|-------------------|
    | mnorm(a0, p)                                                                             |
    |-------------------|-------------------|------------------------------|-------------------|
    |    static p       |  dynamic p        |     formula  (pseudo-code)   |  equivalent to    |
    |-------------------|-------------------|------------------------------|-------------------|
    | nt2::one_         | 1                 |       max(sum(abs(x)))       | mnorm1(x)         |
    | nt2::two_         | 2                 |         max(svd(x))          | mnorm2(x)         |
    | nt2::inf_         | nt2::Inf<T>()     |   max(sum(abs(ctrans(x))))   | mnorminf(x)       |
    | nt2::fro_         | -1                | sqrt(sum(diag(ctrans(x)*x))) | mnormfro(x)       |
    |-------------------|-------------------|------------------------------|-------------------|
    | mnorm<p>(a0)                                                                             |
    |-------------------|-------------------|------------------------------|-------------------|
    |    static p       |                   |     matrix                   |                   |
    |-------------------|-------------------|------------------------------|-------------------|
    | nt2::tag::one_    |        -          |       max(sum(abs(x)))       |  mnorm1(x)        |
    | nt2::tag::two_    |        -          |         max(svd(x))          |  mnorm2(x)        |
    | nt2::tag::inf_    |        -          |   max(sum(abs(ctrans(x))))   |  mnorminf(x)      |
    | nt2::tag::fro_    |        -          | sqrt(sum(diag(ctrans(x)*x))) |  mnormfro(x)      |
    |-------------------|-------------------|------------------------------|-------------------|
    @endcode

    @par Semantic:
    1, 2 and inf can be given dynamically or statically as template parameter ie:

    For any expression @c a0 of type @c A0, the following call:

    @code
    as_real<A0::value_type>::type x = mnorm(a0);
    @endcode

    is equivalent to:

    @code
    as_real<A0::value_type>::type x = svd(a0)(1);
    @endcode

    For any expression @c a0 of type @c A0 and any value x in {one_, two_, inf_, fro_}
    following call:

    @code
    as_real<A0::value_type>::type r = mnorm(a0,nt2::x);
    @endcode

    or

    @code
    as_real<A0::value_type>::type r = mnorm<nt2::tag::x>(a0);
    @endcode
    is equivalent to:

    @code
    as_real<A0::value_type>::type r = mnormx(a0);
    @endcode

    @param a0 Expression to compute the norm of
    @param a1 Type of norm to compute
  **/



  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnorm_, mnorm, 1)

  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnorm_, mnorm, 2)

  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnorm_, mnorm2, 1)

  /// @overload
  template < class T, class A>
  BOOST_FORCEINLINE
  typename meta::as_real<typename A::value_type>::type
  mnorm(const A& a)
  {
    return mnorm(a, nt2::meta::as_<T>());
  }
  /// @overload
  template < int Value, typename A>
  BOOST_FORCEINLINE
  typename meta::as_real<typename A::value_type>::type
  mnorm(const A& a)
  {
    return mnorm(a, boost::mpl::int_<Value>());
  }
}


#endif
