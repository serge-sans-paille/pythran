//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FILL_PATTERN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FILL_PATTERN_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief fill_pattern generic tag

      Represents the fill_pattern function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct fill_pattern_ : ext::elementwise_<fill_pattern_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fill_pattern_> parent;
    };
  }


  #if defined(DOXYGEN_ONLY)
  /*!
    @brief Pattern generator

    Create an array made of a linear repetition of a given pattern matrix.

    @par Semantic:

    fill_pattern semantic depends of its parameters type and quantity:

    - For any Expression @c p and any Integer @c sz1,...,szn , the
      following code:
      @code
      auto x = fill_pattern(p, sz1,...,szn);
      @endcode
      generates an expression that evaluates as a @sizes{sz1,szn} table where,
      for any indexes @c i, <tt>x(i) = p(i%numel(p))</tt>.

    - For any Expression @c p and any Expression @c dims evaluating as a row
      vector of @c N elements, the following code:
      @code
      auto x = fill_pattern(p, dims);
      @endcode
      generates an expression that evaluates as a @sizes{dims(1),dims(N)}
      table  where, for any indexes @c i, <tt>x(i) = p(i%numel(p))</tt>.

    - For any Expression @c p and any Fusion Sequence @c dims of @c N elements,
      the following code:
      @code
      auto x = fill_pattern(p, dims);
      @endcode
      generates an expression that evaluates as a @sizes{at_c<1>(dims),at_c<N-1>(dims)}
      table where, for any indexes @c i, <tt>x(i) = p(i%numel(p))</tt>.

    @usage_output{fill_pattern.cpp,fill_pattern.out}

    @param p  Data patter to repeat in the result.

    @param dims Size of each dimension, specified as one or more integer values
                or as a row vector of integer values. If any @c dims is lesser
                or equal to 0, then the resulting expression is empty.

    @return An Expression evaluating as an array of a given type and dimensions.
  **/
  template<typename Pattern, typename... Dims>
  details::unspecified fill_pattern(Pattern const& p, Args const&... dims);

  #else

  #define M0(z,n,t)                                                     \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::fill_pattern_, fill_pattern, n) \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0

  #endif
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::fill_pattern_,Domain,N,Expr>
        : meta::value_as<Expr,1>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::fill_pattern_,Domain,N,Expr>
        : meta::boxed_size<Expr,0>
  {};
} }

#endif
