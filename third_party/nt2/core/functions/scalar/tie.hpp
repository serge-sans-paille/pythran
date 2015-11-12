//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_TIE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_TIE_HPP_INCLUDED

#include <nt2/core/functions/tie.hpp>
#include <nt2/core/container/dsl/domain.hpp>
#include <boost/dispatch/meta/as_ref.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

namespace nt2 { namespace ext
{
  template<class T, class Enable = void>
  struct as_child_ref;

  template<class T>
  struct as_child_ref_expr
  {
    typedef container::domain::template as_child_expr<T, typename T::proto_tag, false> impl;
    typedef typename impl::result_type type;
    static type call(T& t)
    {
      return impl()(t);
    }
  };

  template<class T, class Enable>
  struct as_child_ref
  {
    typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<T&> > expr;
    typedef nt2::container::expression<expr, T&> type;
    static type call(T& t)
    {
      return type(expr::make(t));
    }
  };

  template<class T>
  struct as_child_ref<T, typename T::proto_is_expr_>
       : as_child_ref_expr<T>
  {
  };

#define M1(z,n,t) (A##n)
#define M2(z,n,t) (unspecified_<A##n>)
#define M2b(z,n,t) (generic_< unspecified_<A##n> >)
#define M3(z,n,t) typename ext::as_child_ref<A##n>::type
#define M4(z,n,t) ext::as_child_ref<A##n>::call(a##n)

#define M0(z,n,t)                                                              \
NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tie_, BOOST_PP_TUPLE_ELEM(2,0,t)         \
                          , BOOST_PP_REPEAT(n,M1,~)                            \
                          , BOOST_PP_REPEAT(n,BOOST_PP_TUPLE_ELEM(2,1,t),~)    \
                          )                                                    \
{                                                                              \
  typedef boost::proto::                                                       \
          basic_expr< nt2::tag::tie_                                           \
                    , boost::proto::list##n<BOOST_PP_ENUM(n, M3, ~)>           \
                    , n                                                        \
                    > expr;                                                    \
  typedef nt2::details::                                                       \
          generator< nt2::tag::tie_                                            \
                   , nt2::container::domain                                    \
                   , n                                                         \
                   , expr const                                                \
                   > generator;                                                \
  typedef typename generator::result_type result_type;                         \
                                                                               \
  BOOST_FORCEINLINE result_type                                                \
  operator()(BOOST_PP_ENUM_BINARY_PARAMS(n,A,& a)) const                       \
  {                                                                            \
    expr e = { BOOST_PP_ENUM(n, M4, ~) };                                      \
    return result_type(e);                                                     \
  }                                                                            \
};                                                                             \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PROTO_MAX_ARITY,M0,(tag::formal_, M2))
BOOST_PP_REPEAT_FROM_TO(1,BOOST_PROTO_MAX_ARITY,M0,(tag::cpu_, M2b))

#undef M0
#undef M1
#undef M2
#undef M2b
#undef M3
#undef M4
} }

#endif
