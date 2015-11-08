//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ALONG_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ALONG_INDEX_HPP_INCLUDED

#include <nt2/core/functions/along_index.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/include/functions/relative_index.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/functions/table/details/is_vectorizable_indexer.hpp>
#include <nt2/core/functions/table/details/reindex.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <boost/mpl/if.hpp>
#include <boost/array.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<nt2::tag::along_index_, Domain, 3 ,Expr>
  {
    typedef typename boost::proto::result_of::
            value< typename boost::proto::result_of::
                   child_c<Expr&, 2>::value_type
                 >::type Sz;
    typedef typename nt2::make_size < Sz::static_size
                                    >::type result_type;

    result_type operator()(Expr& expr) const
    {
      result_type sz = boost::proto::value(boost::proto::child_c<2>(expr));
      std::size_t i = boost::proto::value(boost::proto::child_c<1>(expr));
      BOOST_ASSERT_MSG(i <= result_type::static_size, "Applying indexer along a dimension past the indexed size");
      sz[i-1] = numel(boost::proto::child_c<0>(expr));
      return sz;
    }
  };

  template<class Domain, class Expr>
  struct value_type<nt2::tag::along_index_, Domain, 3, Expr>
  {
    typedef std::size_t type;
  };
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::along_index_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2),
      (boost::proto::make_expr<tag::along_index_, nt2::container::domain>(boost::cref(a0), boost::cref(a1), boost::cref(a2)))
    )
  };

  // TODO: take into account indexes
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_,
                              (A0)(State)(Data),
                              ((node_<A0, nt2::tag::along_index_, boost::mpl::long_<3> , nt2::container::domain>))
                              (generic_< arithmetic_<State> > )
                              (unspecified_<Data>)
                            )
  {
    typedef typename boost::mpl::
            if_< typename is_vectorizable_indexer< typename boost::proto::result_of::child_c<A0, 0>::value_type
                                                 , typename meta::cardinal_of<typename meta::target_value<Data>::type>::type
                                                 >::type
               , State
               , typename details::as_integer_target<Data>::type
               >::type                                        i_t;
    typedef boost::array<i_t, A0::extent_type::static_size>   pos_type;

    typedef i_t result_type;

    result_type operator()(A0& a0, State const& state, Data const&) const
    {
      pos_type p = as_subscript(a0.extent(), nt2::enumerate<i_t>(state));
      std::size_t i = boost::proto::value(boost::proto::child_c<1>(a0));
      if(i <= pos_type::static_size)
        p[i-1] = relative_index( boost::proto::child_c<0>(a0)
                               , std::ptrdiff_t(1) // FIXME
                               , a0.extent()[i-1]
                               , p[i-1]
                               , boost::dispatch::meta::as_<i_t>()
                               );
      return as_index(boost::proto::value(boost::proto::child_c<2>(a0)), p);
    }
  };

} }

#endif
