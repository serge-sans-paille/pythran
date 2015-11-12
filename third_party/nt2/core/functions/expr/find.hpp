//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_FIND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_FIND_HPP_INCLUDED

#include <nt2/core/functions/find.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/findi.hpp>
#include <nt2/include/functions/findj.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/globalfind.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/memory/container_shared_ref.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>

#include <boost/fusion/include/make_vector.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::find_,Domain,N,Expr>
  {
    typedef nt2::_1D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      ptrdiff_t k = boost::proto::value(boost::proto::child_c<1>(e));

      BOOST_ASSERT_MSG( k > 0
                      , "Error using find: second argument "
                        "must be a positive scalar integer."
                      );

      ptrdiff_t n = ptrdiff_t(nt2::nbtrue(nt2::colvect(boost::proto::child_c<0>(e)))(1));
      return result_type((k > 0)? nt2::min(k, n) : 0);
    }
  };

  template<class Domain, class Expr>
  struct  size_of<tag::find_,Domain,1,Expr>
    : meta::size_as<Expr,0>
  {
    typedef nt2::_1D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(nt2::nbtrue(nt2::colvect(boost::proto::child_c<0>(e)))(1));
    }

  };

  template<class Domain, int N, class Expr>
  struct  value_type<tag::find_,Domain,N,Expr>
  {
    typedef std::ptrdiff_t      type;
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::find_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::find_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type       child0;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child1;
    typedef typename boost::dispatch::meta::terminal_of<child0>::type    in0_t;
    typedef typename in0_t::value_type                              value_type;
    typedef typename boost::dispatch::meta::terminal_of<child1>::type    out_t;
    typedef typename out_t::value_type              index_type;
    typedef typename boost::dispatch::meta::as_integer<value_type, unsigned>::type  idx_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      bool    first =  true;
      getparams(a0, first, N0());
      compute(a0, a1, first, N1());
    }
  private :

    BOOST_FORCEINLINE  //    i = find(x, ...)
      void compute(A0 const &a0, A1 & a1, bool& first,
                   boost::mpl::long_<1> const &//number of outputs
                   ) const
    {
      child1& idx = boost::proto::child_c<0>(a1);
      child0& a = boost::proto::child_c<0>(a0);
      idx.resize(extent(a0));
      ptrdiff_t k = numel(idx);
      ptrdiff_t m = nt2::numel(a);
      if(!k) return;
      if(first)
      {
        for(std::ptrdiff_t i=0, z = 0; z!= k; ++i)
        {
          value_type value = nt2::run(a, i, meta::as_<value_type>());
          if(value)
          {
            idx(++z) = index_type(i+1);
          }
        }
      }
      else
      {
        for(std::ptrdiff_t i=m-1, z = k; z!=0; --i)
        {
          value_type value = nt2::run(a, i, meta::as_<value_type>());
          if(value)
          {
            idx(z) = index_type(i+1);
            --z;
          }
        }
      }
    }


    BOOST_FORCEINLINE  //    [i, j]= find(x)
      void compute(A0 const &a0, A1 & a1, bool& first,
                     boost::mpl::long_<2> const &//number of outputs
                     ) const
    {
      child1& idx = boost::proto::child_c<0>(a1);
      child1& jdx = boost::proto::child_c<1>(a1);
      child0& a = boost::proto::child_c<0>(a0);
      idx.resize(extent(a0));
      jdx.resize(extent(a0));
      ptrdiff_t k = numel(idx);
      if(!k) return;
      ptrdiff_t t = nt2::numel(a);
      ptrdiff_t m = nt2::size(a, 1);
      ptrdiff_t n = t/m;
      if(first)
      {
        for(ptrdiff_t i=0, z = 0; z!=k; ++i)
        {
          value_type value = nt2::run(a, i, meta::as_<value_type>());
          if(value)
          {
            boost::array<idx_t, 2> aa = nt2::as_subscript(boost::fusion:: make_vector(idx_t(m),idx_t(n)), idx_t(i) );
            idx(++z) = index_type(aa[1]+1);
            jdx(  z) = index_type(aa[0]+1);
          }
        }
      }
      else
      {
        for(ptrdiff_t i=t-1, z = k+1; z!=0; --i)
        {
          value_type value = nt2::run(a, i, meta::as_<value_type>());
          if(value)
          {
            boost::array<idx_t, 2> aa = nt2::as_subscript(boost::fusion:: make_vector(idx_t(m),idx_t(n)), idx_t(i) );
            idx(z) = index_type(aa[1]+1);
            jdx(z) = index_type(aa[0]+1);
            --z;
          }
        }
      }
    }


    BOOST_FORCEINLINE  //    [i, j]= find(x)
      void compute(A0 const &a0, A1 & a1, bool& first,
                   boost::mpl::long_<3> const &//number of outputs
        ) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,1>::type       child2;
      typedef typename boost::proto::result_of::child_c<A1&,2>::type       child3;
      child1& idx = boost::proto::child_c<0>(a1);
      child2& jdx = boost::proto::child_c<1>(a1);
      child3& v = boost::proto::child_c<2>(a1);
      child0& a = boost::proto::child_c<0>(a0);
      idx.resize(extent(a0));
      jdx.resize(extent(a0));
      v.resize(extent(a0));
      ptrdiff_t k = numel(idx);
      if(!k) return;
      ptrdiff_t t = nt2::numel(a);
      ptrdiff_t m = nt2::size(a, 1);
      ptrdiff_t n = t/m;
      if(first)
      {
        for(ptrdiff_t i=0, z = 0; z!=k; ++i)
        {
          value_type value = nt2::run(a, i, meta::as_<value_type>());
          if(value)
          {
            boost::array<idx_t, 2> aa = nt2::as_subscript(boost::fusion:: make_vector(idx_t(m),idx_t(n)), idx_t(i) );
            idx(++z) = index_type(aa[1]+1);
            jdx(z) = index_type(aa[0]+1);
            v(z) = value;
          }
        }
      }
      else
      {
        for(ptrdiff_t i=t-1, z = k; z!=0; --i)
        {
          value_type value = nt2::run(a, i, meta::as_<value_type>());
          if(value)
          {
            boost::array<idx_t, 2> aa = nt2::as_subscript(boost::fusion:: make_vector(idx_t(m),idx_t(n)), idx_t(i) );
            idx(z) = index_type(aa[1]+1);
            jdx(z) = index_type(aa[0]+1);
            v(z) = value;
            --z;
          }
        }
      }
    }

    BOOST_FORCEINLINE  //    i = find(x)
      void getparams(A0 const &, bool&,
                     boost::mpl::long_<1> const &//number of inputs
        ) const
    {}

    BOOST_FORCEINLINE  //    i = find(x, k)
      void getparams(A0 const &, bool&,
                     boost::mpl::long_<2> const &//number of inputs
        ) const
    {}

    BOOST_FORCEINLINE  //    i = find(x, k, 'f') or i = find(x, k, 'l')
      void getparams(A0 const &a0, bool& first,
                     boost::mpl::long_<3> const &//number of inputs
        ) const
    {
      first = boost::proto::value(boost::proto::child_c<2>(a0));
    }

  };
} }

#endif
