//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COLON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COLON_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief colon generic tag

      Represents the colon function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct colon_ : ext::state_constant_<colon_>
    {
      /// @brief Parent hierarchy
      typedef ext::state_constant_<colon_> parent;

      /// @brief default value type for untyped calls
      typedef double                      default_type;
    };

    /// INTERNAL ONLY
    struct empty_colon_ : colon_
    {
      typedef colon_ parent;
    };

    /// INTERNAL ONLY
    struct relative_colon_ : ext::elementwise_<relative_colon_>
    {
      typedef ext::elementwise_<relative_colon_> parent;
    };
  }

  /*!
    @brief Regular spaced values generator

    Creates an array filled with regularly spaced values.

    @par Semantic

    For any Scalar value @c l and @c h of type @c T, if h >= l, the
    following code:
    @code
    auto x = colon(l,h);
    @endcode

    generates an expression that evaluates as a @size2d{1,h-l+1} table of
    type @c T for which, for any index @c i :

    @code
    x(i) = l + i
    @endcode

    If h < l, the generated expression evaluates an empty table.

    @usage_output{colon.cpp,colon.out}

    @param a0 First value of the generation space
    @param a1 Last value of the generation space

    @return An Expression evaluating as an array of a given type and dimensions.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::colon_, colon, 2)

  /*!
    @brief Regular spaced values generator with step

    Creates an array filled with values regularly spaced with a given step.

    @par Semantic

    For any Scalar value @c l, @c h and @c s of type @c T
    @code
    auto x = colon(l,s,h);
    @endcode

    generates an expression that evaluates as a @size2d{1,fix((h-l+1)/s)}
    table of type @c T for which, for any index @c i :

    @code
    x(i) = l + i*s
    @endcode

    If h < l, the generated expression evaluates an empty table.

    @usage_output{colon_step.cpp,colon_step.out}

    @param a0 First value of the generation space
    @param a1 Step between generated values
    @param a2 Last value of the generation space

    @return An Expression evaluating as an array of a given type and dimensions.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::colon_, colon, 3)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  value_type<tag::colon_,Domain,N,Expr>
        : meta::generative_value<Expr> {};

  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  size_of<tag::colon_,Domain,N,Expr>
        : meta::generative_size<Expr> {};

  template<class Domain, class Expr, int N>
  struct  value_type<tag::empty_colon_,Domain,N,Expr>
        : meta::generative_value<Expr> {};

  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  size_of<tag::empty_colon_,Domain,N,Expr>
        : meta::generative_size<Expr> {};

  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  value_type<tag::relative_colon_,Domain,N,Expr>
  {
    typedef int type;
  };

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct size_of<tag::relative_colon_,Domain,1,Expr>
  {
    typedef of_size_<1, -1> result_type;
    BOOST_FORCEINLINE result_type operator()(Expr&) const
    {
      return result_type();
    }
  };

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct size_of<tag::relative_colon_,Domain,2,Expr>
  {
    typedef of_size_<1, -1> result_type;
    BOOST_FORCEINLINE result_type operator()(Expr&) const
    {
      return result_type();
    }
  };
} }

#endif
