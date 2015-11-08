//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_MINF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_MINF_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/constants/minf.hpp>
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
    @brief minf generator

    Create an array full of negative infinites.

    @par Semantic:

    minf() semantic depends of its parameters type and quantity:

    - The following code:
      @code
      double x = minf();
      @endcode
      is equivalent to
      @code
      double x = -std::numeric_limits<double>::infinity();
      @endcode

    - For any Integer @c n, the following code:
      @code
      auto x = minf(n);
      @endcode
      generates an expression that evaluates as a @c n x @c n table of @c double
      minf.

    - For any Integer @c sz1,...,szN , the following code:
      @code
      auto x = minf(sz1,...,szn);
      @endcode
      generates an expression that evaluates as a @c sz1 x ... x @c szN
      table of @c double negative infinites.

    - For any Expression @c dims evaluating as a row vector of @c N elements,
      the following code:
      @code
      auto x = minf(dims);
      @endcode
      generates an expression that evaluates as a @c dims(1) x ... x @c dims(N)
      table of @c double negative infinites.

    - For any type @c T, the following code:
      @code
      T x = minf( as_<T>() );
      @endcode
      is equivalent to
      @code
      T x = T(1);
      @endcode

    - For any Integer @c n and any type @c T, the following code:
      @code
      auto x = minf(n, as_<T>());
      @endcode
      generates an expression that evaluates as a @c n x @c n table of type @c T
      negative infinites.

    - For any Integer @c sz1,...,szN and any type @c T, the following code:
      @code
      auto x = minf(sz1,...,szn, as_<T>());
      @endcode
      generates an expression that evaluates as a @c sz1 x ... x @c szN
      table of type @c T negative infinites.

    - For any Expression @c dims evaluating as a row vector of @c N elements
      and any type @c T, the following code:
      @code
      auto x = minf(dims, as_<T>());
      @endcode
      generates an expression that evaluates as a @c dims(1) x ... x @c dims(N)
      table of type @c T negative infinites.

    @param dims Size of each dimension, specified as one or more integer values
                or as a row vector of integer values. If any @c dims is lesser
                or equal to 0, then the resulting expression is empty.

    @param classname  Type specifier of the output. If left unspecified, the
                      resulting expression behaves as an array of double.

    @return An Expression evaluating as an array of a given type and dimensions
            full of negative infinites.
  **/
  template<typename... Args, typename ClassName>
  Expression minf(Args const&... dims, ClassName const& classname);

  /// @overload
  template<typename... Args> Expression minf(Args const&... dims);

  /// @overload
  template<typename ClassName> ClassName::type minf(ClassName const& classname);

  /// @overload
  double minf();
  #else

  /// INTERNAL ONLY
  #define M0(z,n,t)                                                            \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::Minf,minf, n)                          \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0
  #endif
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<typename Domain, typename Expr, int N>
  struct  value_type<tag::Minf,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  /// INTERNAL ONLY
  template<typename Domain, typename Expr, int N>
  struct  size_of<tag::Minf,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }
#endif

