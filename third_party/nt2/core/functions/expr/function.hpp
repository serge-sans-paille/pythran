//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_FUNCTION_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_FUNCTION_HPP_INCLUDED

#include <nt2/core/functions/function.hpp>
#include <nt2/memory/functions/assign.hpp>
#include <nt2/include/functions/function_index.hpp>
#include <nt2/include/functions/erase.hpp>
#include <nt2/include/functions/aggregate.hpp>
#include <nt2/include/functions/globalfind.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/core/functions/table/details/is_vectorizable_indexer.hpp>
#include <nt2/core/container/colon/category.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/memory/container_shared_ref.hpp>
#include <nt2/core/settings/add_settings.hpp>
#include <nt2/sdk/meta/as_index.hpp>
#include <nt2/sdk/meta/is_scalar.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <boost/simd/sdk/meta/is_logical.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/utility/enable_if.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::assign_, tag::cpu_
                            , (A0)(N0)(I0)
                            , ((node_<A0, nt2::tag::function_, N0, nt2::container::domain>))
                              ((node_<I0, nt2::tag::empty_colon_, boost::mpl::long_<3>, nt2::container::domain>))
                            )
  {
    typedef A0& result_type;

    result_type operator()(A0& a0, I0&) const
    {
      typedef typename A0::proto_child0::proto_child0 container_ref;
      typedef typename container_ref::base_t base_t;
      typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<base_t&>, 0l> basic_expr;
      typedef nt2::container::expression<basic_expr, base_t&> nt2_expr;

      nt2_expr c(basic_expr::make(static_cast<base_t&>(*boost::proto::value(boost::proto::child_c<0>(a0)).base())));
      nt2::erase(c, boost::proto::child_c<0>(boost::proto::child_c<1>(a0)));
      return a0;
    }
  };

  // handle erase for a(_, 1) = _(), lhs is a terminal because contiguous
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::assign_, tag::cpu_
                            , (A0)(I0)
                            , ((node_<A0, nt2::tag::terminal_, boost::mpl::long_<0>, nt2::container::domain>))
                              ((node_<I0, nt2::tag::empty_colon_, boost::mpl::long_<3>, nt2::container::domain>))
                            )
  {
    typedef A0& result_type;

    result_type operator()(A0& a0, I0& i0) const
    {
      return (*this)(a0, i0, typename meta::is_container<typename A0::proto_child0>::type());
    }


    result_type operator()(A0& a0, I0&, boost::mpl::true_) const
    {
      a0.resize(nt2::of_size(0));
      return a0;
    }

    result_type operator()(A0& a0, I0&, boost::mpl::false_) const
    {
      typedef typename A0::proto_child0 container_ref;
      typedef typename container_ref::base_t base0_t;
      typedef typename meta::add_settings<base0_t, _4D>::type base_t;

      typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<base_t&>, 0l> basic_expr;
      typedef nt2::container::expression<basic_expr, base_t&> nt2_expr;

      // FIXME: this static_cast isn't really safe
      nt2_expr c(basic_expr::make(static_cast<base_t&>(*boost::proto::value(a0).base())));
      std::size_t b = c.raw()-a0.raw();
      nt2::erase(c, nt2::aggregate(_(b+1u, b+numel(a0))));
      return a0;
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::function_, tag::cpu_
                            , (A0)(I0)
                            , ((ast_<A0, nt2::container::domain>))(colon_<I0>)
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS ( 2
                                , (A0& a0, I0 const& io)
                                , (A0& a0, I0 const&)
                                , nt2::colvect(a0)
                                );
  };

  template<class A0, class T, class Dummy = void>
  struct function_find
  {
    typedef T type;
    static T const& call(A0&, T const& t)
    {
      return t;
    }
  };

  template<class A0, class T>
  struct function_find<A0, T, typename boost::enable_if< boost::simd::meta::is_logical<typename T::value_type> >::type>
  {
    typedef typename A0::value_type stype;
    typedef typename meta::as_index<stype>::type itype;
    typedef typename meta::call<tag::globalfind_(T const&, meta::as_<itype>)>::type type;
    static type call(A0&, T const& t)
    {
      return nt2::globalfind(t, meta::as_<itype>());
    }
  };

  template<class A0, class I, bool B = A0::proto_arity_c == 0 && is_contiguous_indexers<I>::value>
  struct function_impl
  {
    typedef typename boost::proto::result_of::
            make_expr < nt2::tag::function_
                      , container::domain
                      , A0&
                      , typename meta::
                        call< tag::function_index_( I const&
                                                  , typename A0::extent_type
                                                  , meta::as_<typename A0::indexes_type>
                                                  )
                            >::type
                      >::type type;

    static type call(A0& a0, I const& indices)
    {
      return boost::proto::make_expr<tag::function_,container::domain>
                                    ( boost::reference_wrapper<A0>(a0)
                                    , function_index(indices, a0.extent(), meta::as_<typename A0::indexes_type>())
                                    );
    }
  };

  template<class A0, class I>
  struct function_impl<A0, I, true>
  {
    // A0's semantic is a container
    template<bool B, class Dummy = void>
    struct impl
    {
      typedef typename meta::
              call< tag::function_index_( I const&
                                        , typename A0::extent_type
                                        , meta::as_<typename A0::indexes_type>
                                        )
                  >::type Idx;

      typedef typename container::as_view_impl<A0>::type type0;
      typedef typename meta::add_settings<type0, typename Idx::extent_type>::type type;

      typedef typename type::nt2_expression nt2_expr;
      typedef typename nt2_expr::proto_base_expr basic_expr;
      typedef typename type::proto_child0 container_ref;

      static type call(A0& a0, I const& indices)
      {
        Idx idx = nt2::function_index(indices, a0.extent(), meta::as_<typename A0::indexes_type>());
        std::size_t b = nt2::run(idx, 0u, meta::as_<std::size_t>());

        return nt2_expr(basic_expr::make(container_ref(boost::proto::value(a0), boost::proto::value(a0).begin()+b, idx.extent())));
      }
    };

    // A0's semantic is a scalar, we can't use views
    template<class Dummy>
    struct impl<true, Dummy>
    {
      typedef typename boost::dispatch::meta::semantic_of<A0>::type type;
      static type call(A0& a0, I const&)
      {
        return a0;
      }
    };

    typedef impl< meta::is_scalar< typename boost::dispatch::meta::semantic_of<A0>::type >::value > impl_;

    typedef typename impl_::type type;
    static type call(A0& a0, I const& indices)
    {
      return impl_::call(a0, indices);
    }
  };

#define M1(z,n,t) (I##n)
#define M2(z,n,t) (unspecified_<I##n>)
#define M3(z,n,t) typename nt2::ext::function_find<A0, I##n>::type
#define M4(z,n,t) function_find<A0, I##n>::call(a0, i##n)

#define M0(z,n,t)                                                                                  \
NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::function_, tag::cpu_                                         \
                          , (A0)BOOST_PP_REPEAT(n,M1,~)                                            \
                          , ((ast_<A0, nt2::container::domain>))BOOST_PP_REPEAT(n,M2,~)            \
                          )                                                                        \
{                                                                                                  \
  typedef typename meta::                                                                          \
          call< tag::aggregate_(BOOST_PP_ENUM(n, M3, ~))                                           \
              >::type                                             indices;                         \
                                                                                                   \
  typedef function_impl<A0, indices> impl;                                                         \
  typedef typename impl::type result_type;                                                         \
                                                                                                   \
  BOOST_FORCEINLINE result_type                                                                    \
  operator()(A0& a0, BOOST_PP_ENUM_BINARY_PARAMS(n,const I,& i) ) const                            \
  {                                                                                                \
    return impl::call(a0, nt2::aggregate(BOOST_PP_ENUM(n,M4,~)));                                  \
  }                                                                                                \
};                                                                                                 \
/**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

#undef M0
#undef M1
#undef M2
#undef M3
#undef M4
} }

#endif
