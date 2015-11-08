//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EYE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EYE_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/functions/details/eye.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/core/functions/common/generative.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief eye generic tag

      Represents the eye function in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( eye_, double
                                , 1, 0x3f800000UL, 0x3ff0000000000000ULL
                                )
  }

  #if defined(DOXYGEN_ONLY)
  /*!
    @brief Identity matrix

    Create an array containing the identity matrix

    @par Semantic:

    eye() semantic depends of its parameters type and quantity:

    - The following code:
      @code
      double x = eye();
      @endcode
      is equivalent to
      @code
      double x = 1.;
      @endcode

    - For any Integer @c n, the following code:
      @code
      auto x = eye(n);
      @endcode
      generates an expression that evaluates as a @size2d{n,n} identity matrix.

    - For any Integer @c sz1,...,szn , the following code:
      @code
      auto x = eye(sz1,...,szn);
      @endcode
      generates an expression that evaluates as a @sizes{sz1,szn} identity matrix.

    - For any Expression @c dims evaluating as a row vector of @c N elements,
      the following code:
      @code
      auto x = eye(dims);
      @endcode
      generates an expression that evaluates as a @sizes{dims(1),dims(N)}
      identity matrix.

    - For any Fusion Sequence @c dims of @c N elements, the following code:
      @code
      auto x = eye(dims);
      @endcode
      generates an expression that evaluates as a @sizes{at_c<0>(dims),at_c<N-1>(dims)}
      identity matrix.

    - For any type @c T, the following code:
      @code
      T x = eye( as_<T>() );
      @endcode
      is equivalent to
      @code
      T x = T(1);
      @endcode

    - For any Integer @c n and any type @c T, the following code:
      @code
      auto x = eye(n, as_<T>());
      @endcode
      generates an expression that evaluates as a @size2d{n,n} table
      identity matrix of type @c T.

    - For any Integer @c sz1,...,szN and any type @c T, the following code:
      @code
      auto x = eye(sz1,...,szn, as_<T>());
      @endcode
      generates an expression that evaluates as a @sizes{sz1,szn} identity
      matrix of type @c T.

    - For any Expression @c dims evaluating as a row vector of @c N elements
      and any type @c T, the following code:
      @code
      auto x = eye(dims, as_<T>());
      @endcode
      generates an expression that evaluates as a @sizes{dims(1),dims(N)}
      identity matrix of type @c T.

    - For any Fusion Sequence @c dims of @c N elements and any type @c T, the
      following code:
      @code
      auto x = eye(dims, as_<T>());
      @endcode
      generates an expression that evaluates as a @sizes{at_c<0>(dims),at_c<N-1>(dims)}
      identity matrix of type @c T.

    @par Matlab equivalent:

    This function is equivalent to the Matlab function
    <a href="http://www.mathworks.com/help/matlab/ref/eye.html">eye</a>.
    eye() doesn't however support the @c like based function. One can actually
    use the class_ function to generate a Type specifier or use such a
    predefined specifier.

    @usage_output{eye.cpp,eye.out}

    @param dims Size of each dimension, specified as one or more integer values
                or as a row vector of integer values. If any @c dims is lesser
                or equal to 0, then the resulting expression is empty.

    @param classname  Type specifier of the output. If left unspecified, the
                      resulting expression behaves as an array of double.

    @return An Expression evaluating as an array of a given type and dimensions.
  **/
  template<typename... Args, typename ClassName>
  details::unspecified eye(Args const&... dims, ClassName const& classname);

  /// @overload
  template<typename... Args> details::unspecified eye(Args const&... dims);

  /// @overload
  template<typename ClassName> ClassName::type eye(ClassName const& classname);

  /// @overload
  double eye();

  #else

  #define M0(z,n,t)                                                            \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::eye_, eye, n)                          \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0

  #endif
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  value_type<tag::eye_,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<tag::eye_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

#endif
