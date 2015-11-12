//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COLS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COLS_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/functions/details/cols.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief cols generic tag

      Represents the cols function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct cols_ : ext::state_constant_<cols_>
    {
      /// @brief Parent hierarchy
      typedef ext::state_constant_<cols_> parent;

      /// @brief default value type for untyped calls
      typedef double                      default_type;
    };
  }

  #if defined(DOXYGEN_ONLY)
  /*!
    @brief Column index generator

    Create an array where every element is equal to its column index in an
    arbitrary base indexing.

    @par Semantic:

    cols() semantic depends of its parameters type and quantity:

    - For any base index @c b of type @c T, the following code:
      @code
      auto x = cols(b);
      @endcode
      is equivalent to
      @code
      T x = b;
      @endcode

    - For any base index @c b of type @c T and any Integer @c sz1,...,szn ,
      the following code:
      @code
      auto x = cols(sz1,...,szn, b);
      @endcode
      generates an expression that evaluates as a @sizes{sz1,szn} table where, for
      any indexes @c i and @c j, <tt>x(i,j) = T(j+b-1)</tt>

    - For any base index @c b of type @c T and any Expression @c dims evaluating
      as a row vector of @c N elements,
      the following code:
      @code
      auto x = cols(dims,b);
      @endcode
      generates an expression that evaluates as a @sizes{dims(1),dims(N)}
      table  where, for any indexes @c i and @c j, <tt>x(i,j) = T(j+b-1)</tt>

    - For any base index @c b of type @c T and any Fusion Sequence @c dims of @c
      N elements, the following code:
      @code
      auto x = cols(dims,b);
      @endcode
      generates an expression that evaluates as a @sizes{at_c<1>(dims),at_c<N-1>(dims)}
      table where, for any indexes @c i and @c j, <tt>x(i,j) = T(j+b-1)</tt>

    @usage_output{cols.cpp,cols.out}

    @param dims Size of each dimension, specified as one or more integer values
                or as a row vector of integer values. If any @c dims is lesser
                or equal to 0, then the resulting expression is empty.

    @param base  Type specifier of the output. If left unspecified, the
                      resulting expression behaves as an array of double.

    @return An Expression evaluating as an array of a given type and dimensions.
  **/
  template<typename... Args, typename Index>
  details::unspecified cols(Args const&... dims, Index const& base);

  /// @overload
  template<typename Index> details::unspecified cols(Index const& base);

  #else

  #define M0(z,n,t)                                     \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cols_, cols, n) \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0

  #endif
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  value_type<tag::cols_,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  size_of<tag::cols_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

#endif
