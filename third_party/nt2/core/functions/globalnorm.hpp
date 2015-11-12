//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALNORM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALNORM_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <boost/mpl/int.hpp>

namespace nt2 { namespace tag
  {
    /*!
      @brief globalnorm generic tag

      Represents the globalnorm function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct globalnorm_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Global norm

    Computes the norm of a whole table expression with static or dynamic choice
    of the norm computation formula.

    Call protocols to globalnorm are summarized in the following table. We advise to use static
    calls whenever possible as it prevents cascaded run-time if clauses and goes directly
    to the right call at execution.

    @code
    |--------------------|-------------------|------------------------------|-------------------|
    | mnorm(a0, p)                                                                              |
    |--------------------|-------------------|------------------------------|-------------------|
    |    static p        |  dynamic p        |     formula (pseudo-code)    |  equivalent to    |
    |--------------------|-------------------|------------------------------|-------------------|
    | nt2::one_          | 1                 |       sum(abs(x(_)))         | globalnorm1(x)    |
    | nt2::two_          | 2                 |   sqrt(sum(sqr(abs(x(_)))))  | globalnorm2(x)    |
    |    -               | p (positive)      |    sum(abs(x)^p)^(1/p)       | globalnormp(x,p)  |
    | nt2::inf_          | nt2::Inf<T>()     |       max(abs((x))           | globalnorminf(x)  |
    | nt2::fro_          | -1                |   sqrt(sum(sqr(abs(x(_)))))  | globalnormfro(x)  |
    |--------------------|-------------------|------------------------------|-------------------|
    | mnorm<p>(a0)                                                                              |
    |--------------------|-------------------|------------------------------|-------------------|
    |    static p        |                   |     matrix                   |                   |
    |--------------------|-------------------|------------------------------|-------------------|
    | nt2::tag::one_ or 1|        -          |       sum(abs(x(_)))         |  globalnorm1(x)   |
    | nt2::tag::two_ or 2|        -          |   sqrt(sum(sqr(abs(x(_)))))  |  globalnorm2(x)   |
    | p  (integer only)  |        -          |    sum(abs(x)^p)^(1/p)       |  globalnormp(x,p) |
    | nt2::tag::inf_     |        -          |       max(abs((x))           |  globalnorminf(x) |
    | nt2::tag::fro_     |        -          |   sqrt(sum(sqr(abs(x(_)))))  |  globalnormfro(x) |
    |--------------------|-------------------|------------------------------|-------------------|
    @endcode

    @par Semantic:

    For any expression @c a0 of type @c A0, the following call:

    @code
    as_real<A0::value_type>::type x = globalnorm(a0);
    @endcode

    is equivalent to:

    @code
    as_real<A0::value_type>::type x = globalnorm2(a0);
    @endcode

    For any expression @c a0 of type @c A0 and any floating point value @c p, the
    following call:

    @code
    as_real<A0::value_type>::type x = globalnorm(a0,p);
    @endcode

    is equivalent to:

    @code
    as_real<A0::value_type>::type x = globalnormp(a0,p);
    @endcode

    if @c p is finite and to :

    @code
    as_real<A0::value_type>::type x = globalmax(abs(a0));
    @endcode

    if @c is +Inf and to :

    @code
    as_real<A0::value_type>::type x = globalmin(abs(a0));
    @endcode

    if @c p is -Inf.

    @note If 0 < p < 1 or p = -inf, globalnorm does not share the properties that
    define a mathematical norm,  but only a quasi-norm if  0 < p < 1 and a notation
    facility for p = -inf.

    @par Static Interface

    globalnorm can also be invoked with a template parameter which is either a
    functor tag describing the constant value to use instead of @c p or an
    Integral Constant. For example,

    @code
    as_real<A0::value_type>::type x = globalnorm<tag::two_>(a0);
    @endcode

    is equivalent to:

    @code
    as_real<A0::value_type>::type x = globalnorm2(a0);
    @endcode

    Similarly,

    @code
    as_real<A0::value_type>::type x = globalnorm<5>(a0);
    @endcode

    is equivalent to:

    @code
    as_real<A0::value_type>::type x = globalnormp(a0,5);
    @endcode

    @note Whenever a constant functor tag or an Integral Constant is used, compile
    time optimization is performed (if available) so the correct variant of globalnorm is
    called. For example, calls similar to globalnorm<2>(a0) will invoke
    globalnorm2(a0) instead of globalnormp(a0, 2), and globalnorm<5>(a0) will simply
    invoke directly globalnormp(a0, 5) but without any runtime selection.

    @param a0 Expression to compute the norm of
    @param a1 Type of norm to compute
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(nt2::tag::globalnorm_, globalnorm, 2)

  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(nt2::tag::globalnorm_, globalnorm, 1)

  /// @overload
  template<typename Tag, typename A0>
  BOOST_FORCEINLINE typename meta::as_real<typename A0::value_type>::type
  globalnorm(const A0& a0)
  {
    return globalnorm(a0, nt2::meta::as_<Tag>());
  }

  /// @overload
  template<int Value, typename A0>
  BOOST_FORCEINLINE typename meta::as_real<typename A0::value_type>::type
  globalnorm(const A0& a0)
  {
    return globalnorm(a0, boost::mpl::int_<Value>() );
  }
}

#endif
