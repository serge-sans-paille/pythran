//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_SIZE_ELEMENTWISE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_SIZE_ELEMENTWISE_HPP_INCLUDED

#include <nt2/core/utility/of_size.hpp>
#include <boost/proto/fusion.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace details
{
  struct get_extent
  {
    template<class Sig>
    struct result;

    template<class This, class T>
    struct result<This(T)>
    {
      typedef typename boost::remove_reference<T>::type sT;
      typedef typename sT::extent_type const& type;
    };

    template<class T>
    BOOST_FORCEINLINE typename T::extent_type const&
    operator()(T const& t) const
    {
      return t.extent();
    }
  };
} }

namespace nt2 { namespace ext
{
  // element-wise size selection logic
  struct size_fold
  {
    template<class A0, class A1, class Dummy = void>
    struct select;

    template<class Sig>
    struct result;

    template<class This, class A0, class A1>
    struct result<This(A0, A1)>
    {
      typedef typename
      select< typename meta::strip<A0>::type
            , typename meta::strip<A1>::type
            >::type type;
    };

    template<class A1, class Dummy>
    struct select<_0D, A1, Dummy>
    {
      typedef A1 type;
    };
    template<class A1>
    BOOST_FORCEINLINE
    typename result<size_fold(_0D const&, A1 const&)>::type
    operator()(_0D const&, A1 const& a1) const
    {
      return a1;
    }

    template<class A0, class Dummy>
    struct select<A0, _0D, Dummy>
    {
      typedef A0 type;
    };
    template<class A0>
    BOOST_FORCEINLINE
    typename result<size_fold(A0 const&, _0D const&)>::type
    operator()(A0 const& a0, _0D const&) const
    {
      return a0;
    }

    template<class Dummy>
    struct select<_0D, _0D, Dummy>
    {
      typedef _0D type;
    };
    BOOST_FORCEINLINE
    result<size_fold(_0D const&, _0D const&)>::type
    operator()(_0D const& a0, _0D const&) const
    {
      return a0;
    }

    template<class A0, class A1, class Dummy>
    struct select
    {
      typedef typename
      boost::mpl::if_c< A0::static_status,A0,A1>::type type;
    };

    template<class A0, class A1> BOOST_FORCEINLINE
    typename result<size_fold(A0 const&, A1 const&)>::type
    operator()(A0 const& a0, A1 const& a1) const
    {
      BOOST_ASSERT_MSG(a0 == a1, "Sizes are not compatible");
      return selection(a0,a1,boost::mpl::bool_<A0::static_status>());
    }

    template<class A0, class A1> BOOST_FORCEINLINE
    typename result<size_fold(A0 const&, A1 const&)>::type
    selection(A0 const& a0, A1 const&, boost::mpl::true_ const&) const
    {
      return a0;
    }

    template<class A0, class A1> BOOST_FORCEINLINE
    typename result<size_fold(A0 const&, A1 const&)>::type
    selection(A0 const&, A1 const& a1, boost::mpl::false_ const&) const
    {
      return a1;
    }
  };

  template<typename Expr, int N>
  struct elementwise_size
  {
    typedef typename boost::fusion::result_of::
    transform<Expr const, details::get_extent>::type sizes;

    typedef typename boost::fusion::result_of::at_c<sizes, 0>::type init;

    typedef typename boost::fusion::result_of::
    fold<sizes, init, size_fold>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      sizes sz = boost::fusion::transform(e, details::get_extent());
      return boost::fusion::fold(sz, boost::fusion::at_c<0>(sz), size_fold());
    }
  };

  template<typename Expr> struct elementwise_size<Expr,1>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type child0;
    typedef typename child0::extent_type result_type;

    BOOST_FORCEINLINE
    result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e).extent();
    }
  };

  template<class Tag, class Domain, int N, class Expr>
  struct size_of
       : elementwise_size<Expr,N>
  {
  };
} }

#endif
