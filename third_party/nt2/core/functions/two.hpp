//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TWO_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TWO_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/core/functions/common/generative.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2
{
  #if defined(DOXYGEN_ONLY)
  /*!
    @brief Two generator

    Create an array full of 2.

    @par Semantic:

    two() semantic depends of its parameters type and quantity:

    - The following code:
      @code
      double x = two();
      @endcode
      is equivalent to
      @code
      double x = 2.;
      @endcode

    - For any Integer @c n, the following code:
      @code
      auto x = two(n);
      @endcode
      generates an expression that evaluates as a @size2d{n,n} table filled with
      @c double 2.

    - For any Integer @c sz1,...,szn , the following code:
      @code
      auto x = two(sz1,...,szn);
      @endcode
      generates an expression that evaluates as a @sizes{sz1,szn} table filled
      @c double 2.

    - For any Expression @c dims evaluating as a row vector of @c N elements,
      the following code:
      @code
      auto x = two(dims);
      @endcode
      generates an expression that evaluates as a @sizes{dims(1),dims(N)}
      table filled with @c double 2.

    - For any Fusion Sequence @c dims of @c N elements, the following code:
      @code
      auto x = two(dims);
      @endcode
      generates an expression that evaluates as a @sizes{at_c<0>(dims),at_c<N-1>(dims)}
      table filled with @c double 2.

    - For any type @c T, the following code:
      @code
      T x = two( as_<T>() );
      @endcode
      is equivalent to
      @code
      T x = T(2);
      @endcode

    - For any Integer @c n and any type @c T, the following code:
      @code
      auto x = two(n, as_<T>());
      @endcode
      generates an expression that evaluates as a @size2d{n,n} table filled with
      type @c T twos.

    - For any Integer @c sz1,...,szN and any type @c T, the following code:
      @code
      auto x = two(sz1,...,szn, as_<T>());
      @endcode
      generates an expression that evaluates as a @sizes{sz1,szn} table filled
      with type @c T twos.

    - For any Expression @c dims evaluating as a row vector of @c N elements
      and any type @c T, the following code:
      @code
      auto x = two(dims, as_<T>());
      @endcode
      generates an expression that evaluates as a @sizes{dims(1),dims(N)}
      table filled with type @c T twos.

    - For any Fusion Sequence @c dims of @c N elements and any type @c T, the
      following code:
      @code
      auto x = two(dims, as_<T>());
      @endcode
      generates an expression that evaluates as a @sizes{at_c<0>(dims),at_c<N-1>(dims)}
      table filled with type @c T twos.

    @param dims Size of each dimension, specified as one or more integer values
                or as a row vector of integer values. If any @c dims is lesser
                or equal to 0, then the resulting expression is empty.

    @param classname  Type specifier of the output. If left unspecified, the
                      resulting expression behaves as an array of double.

    @return An Expression evaluating as an array of a given type and dimensions
            filled with the @c Two constant.

    @sa Two
  **/
  template<typename... Args, typename ClassName>
  details::unspecified two(Args const&... dims, ClassName const& classname);

  /// @overload
  template<typename... Args> details::unspecified two(Args const&... dims);

  /// @overload
  template<typename ClassName> ClassName::type two(ClassName const& classname);

  /// @overload
  double two();

  #else

  #define M0(z,n,t)                                                            \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::Two,two, n)                            \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0

  #endif
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<typename Domain, typename Expr, int N>
  struct  value_type<tag::Two,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  /// INTERNAL ONLY
  template<typename Domain, typename Expr, int N>
  struct  size_of<tag::Two,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }
#endif

