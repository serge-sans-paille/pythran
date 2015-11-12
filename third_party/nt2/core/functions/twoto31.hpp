//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TWOTO31_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TWOTO31_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/constants/twoto31.hpp>
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
    @brief Twoto31 generator

    Create an array full of the Twoto31 constant.

    @par Semantic:

    twoto31() semantic depends of its parameters type and quantity:

    - The following code:
      @code
      double x = twoto31();
      @endcode
      is equivalent to
      @code
      double x = Twoto31<double>();
      @endcode

    - For any Integer @c n, the following code:
      @code
      auto x = twoto31(n);
      @endcode
      generates an expression that evaluates as a @size2d{n,n} table filled with
      the <tt>Twoto31<double>()</tt> value.

    - For any Integer @c sz1,...,szn , the following code:
      @code
      auto x = twoto31(sz1,...,szn);
      @endcode
      generates an expression that evaluates as a @sizes{sz1,szn} table filled
      with the <tt>Twoto31<double>()</tt> value.

    - For any Expression @c dims evaluating as a row vector of @c N elements,
      the following code:
      @code
      auto x = twoto31(dims);
      @endcode
      generates an expression that evaluates as a @sizes{dims(1),dims(N)}
      table filled with the <tt>Twoto31<double>()</tt> value.

    - For any Fusion Sequence @c dims of @c N elements, the following code:
      @code
      auto x = twoto31(dims);
      @endcode
      generates an expression that evaluates as a @sizes{at_c<0>(dims),at_c<N-1>(dims)}
      table filled with the <tt>Twoto31<double>()</tt> value.

    - For any type @c T, the following code:
      @code
      T x = twoto31( as_<T>() );
      @endcode
      is equivalent to
      @code
      T x = Twoto31<T>();
      @endcode

    - For any Integer @c n and any type @c T, the following code:
      @code
      auto x = twoto31(n, as_<T>());
      @endcode
      generates an expression that evaluates as a @size2d{n,n} table filled with
      the <tt>Twoto31<T>()</tt> value.

    - For any Integer @c sz1,...,szN and any type @c T, the following code:
      @code
      auto x = twoto31(sz1,...,szn, as_<T>());
      @endcode
      generates an expression that evaluates as a @sizes{sz1,szn} table filled
      with the <tt>Twoto31<T>()</tt> value.

    - For any Expression @c dims evaluating as a row vector of @c N elements
      and any type @c T, the following code:
      @code
      auto x = twoto31(dims, as_<T>());
      @endcode
      generates an expression that evaluates as a @sizes{dims(1),dims(N)}
      table filled with the <tt>Twoto31<T>()</tt> value.

    - For any Fusion Sequence @c dims of @c N elements and any type @c T, the
      following code:
      @code
      auto x = twoto31(dims, as_<T>());
      @endcode
      generates an expression that evaluates as a @sizes{at_c<0>(dims),at_c<N-1>(dims)}
      table filled with the <tt>Twoto31<T>()</tt> value.

    @param dims Size of each dimension, specified as one or more integer values
                or as a row vector of integer values. If any @c dims is lesser
                or equal to 0, then the resulting expression is empty.

    @param classname  Type specifier of the output. If left unspecified, the
                      resulting expression behaves as an array of double.

    @return An Expression evaluating as an array of a given type and dimensions
            filled with the @c Twoto31 constant.

    @sa Twoto31
  **/
  template<typename... Args, typename ClassName>
  details::unspecified twoto31(Args const&... dims, ClassName const& classname);

  /// @overload
  template<typename... Args> details::unspecified twoto31(Args const&... dims);

  /// @overload
  template<typename ClassName> ClassName::type twoto31(ClassName const& classname);

  /// @overload
  double twoto31();

  #else

  #define M0(z,n,t)                                                            \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::Twoto31,twoto31, n)                    \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0

  #endif
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<typename Domain, typename Expr, int N>
  struct  value_type<tag::Twoto31,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  /// INTERNAL ONLY
  template<typename Domain, typename Expr, int N>
  struct  size_of<tag::Twoto31,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }
#endif

