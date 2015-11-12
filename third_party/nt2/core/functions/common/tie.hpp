#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_TIE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_TIE_HPP_INCLUDED

#include <nt2/core/functions/tie.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/container_traits.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/meta/is_scalar.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/cat.hpp>

#define FUNCTION_PARAMS(z,n,t) BOOST_PP_TUPLE_ELEM(3, 0, t) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(3, 1, t), n) BOOST_PP_TUPLE_ELEM(3, 2, t)
#define BOOST_PP_ITERATION_PARAMS_1 (3, ( 1, BOOST_DISPATCH_MAX_ARITY, "nt2/core/functions/common/tie.hpp"))
#include BOOST_PP_ITERATE()
#undef FUNCTION_PARAMS

namespace nt2 { namespace ext
{
  template<class Domain, class Expr>
  struct value_type<tag::assign_, Domain, 2, Expr>
  {
    // the usual; assignment behaves like assignment on the scalar values
    template<class Tag, bool B, class Dummy = void>
    struct impl
         : meta::call<tag::assign_( typename meta::scalar_of< typename boost::dispatch::meta::semantic_of< typename boost::proto::result_of::child_c<Expr&, 0>::type >::type >::type
                                  , typename meta::scalar_of< typename boost::dispatch::meta::semantic_of< typename boost::proto::result_of::child_c<Expr&, 1>::type >::type >::type
                                  )
                     >
    {
    };

    // if tie is used, we assume the semantic of assigning a value to
    // a fusion sequence is always valid if assigning the first element is
    // TODO: make nodes specify their semantic per output arity?
    template<class Dummy>
    struct impl<tag::tie_, false, Dummy>
         : meta::call<tag::assign_( typename meta::scalar_of< typename boost::fusion::result_of::at_c< typename boost::dispatch::meta::semantic_of< typename boost::proto::result_of::child_c<Expr&, 0>::type >::type, 0 >::type >::type
                                  , typename meta::scalar_of< typename boost::dispatch::meta::semantic_of< typename boost::proto::result_of::child_c<Expr&, 1>::type >::type >::type
                                  )
                     >
    {
    };

    typedef impl< typename Expr::proto_child0::proto_tag
                , boost::fusion::traits::
                  is_sequence< typename boost::dispatch::meta::
                               semantic_of< typename Expr::proto_child1 >::type
                             >::value
                > impl_;
    typedef typename impl_::type type;
  };

  // resizing a tie resizes all arguments
  template<class Domain, int N, class Expr>
  struct resize<tag::tie_, Domain, N, Expr>
  {
    template<class Sz>
    struct impl
    {
      BOOST_FORCEINLINE impl(Expr& x_, Sz const& sz_) : x(x_), sz(sz_) {}

      template<int I>
      BOOST_FORCEINLINE void operator()() const
      {
        boost::proto::child_c<I>(x).resize(sz);
      }

      Expr& x;
      Sz const& sz;

      private:
      impl& operator=(impl const&);
    };

    template<class Sz>
    BOOST_FORCEINLINE void operator()(Expr& x, Sz const& sz)
    {
      boost::simd::meta::iterate<N>(impl<Sz>(x, sz));
    }
  };

  // semantic of assigning a fusion sequence to a fusion sequence is assumed
  // to always be valid if assigning the first element is
  // TODO: check other elements?
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::assign_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename boost::fusion::result_of::at_c<A0, 0>::type first;
    typedef typename boost::fusion::result_of::at_c<A1, 0>::type first2;
    typedef typename meta::call<tag::assign_(first, first2)>::type result_type;
  };

  // semantic of assigning a fusion sequence to a value can
  // only take the first value
  // Not allowed if the fusion sequence is actually a scalar
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::assign_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< unspecified_<A0> >)
                              (fusion_sequence_<A1>)
                            )
  {
    BOOST_MPL_ASSERT_MSG( !boost::dispatch::meta::is_scalar<A1>::value, NT2_ASSIGN_SCALAR_SEQUENCE, (A0, A1) );

    typedef typename boost::fusion::result_of::at_c<A1, 0>::type first;
    typedef typename meta::call<tag::assign_(A0&, first)>::type result_type;

    result_type operator()(A0& a0, A1 const& a1) const
    {
      return a0 = boost::fusion::at_c<0>(a1);
    }
  };
} }

#endif
#else
#define n BOOST_PP_ITERATION()

namespace boost { namespace dispatch { namespace meta
{
  template<BOOST_PP_ENUM_PARAMS(n, class A)>
  struct value_of< boost::fusion::BOOST_PP_CAT(vector, n)<BOOST_PP_ENUM_PARAMS(n, A)> >
  {
    typedef boost::fusion::BOOST_PP_CAT(vector, n)< BOOST_PP_ENUM(n, FUNCTION_PARAMS, (typename value_of<, A, >::type)) > type;
  };

  // necessary because otherwise scalar_of doesn't know that vector1< complex<T> > is a scalar
  template<BOOST_PP_ENUM_PARAMS(n, class A)>
  struct scalar_of< boost::fusion::BOOST_PP_CAT(vector, n)<BOOST_PP_ENUM_PARAMS(n, A)> >
  {
    typedef boost::fusion::BOOST_PP_CAT(vector, n)< BOOST_PP_ENUM(n, FUNCTION_PARAMS, (typename scalar_of<, A, >::type)) > type;
  };
} } }

namespace nt2 { namespace meta
{
  // necessary otherwise references on the elements to do not get stripped
  template<BOOST_PP_ENUM_PARAMS(n, class A)>
  struct value_type_< boost::fusion::BOOST_PP_CAT(vector, n)<BOOST_PP_ENUM_PARAMS(n, A)> >
  {
    typedef boost::fusion::BOOST_PP_CAT(vector, n)< BOOST_PP_ENUM(n, FUNCTION_PARAMS, (typename value_type_<, A, >::type)) > type;
  };
} }

#undef n
#endif
