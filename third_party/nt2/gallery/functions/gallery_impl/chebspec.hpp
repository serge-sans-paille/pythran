//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_CHEBSPEC_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_CHEBSPEC_HPP_INCLUDED

#include <nt2/gallery/functions/chebspec.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/constants/six.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/ric.hpp>
#include <nt2/include/functions/cic.hpp>
#include <nt2/include/functions/cospi.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/is_even.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebspec_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::chebspec_
                                          , container::domain
                                          , A0 const&, A1 const&
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1) const
    {
      return  boost::proto
            ::make_expr < nt2::tag::chebspec_
                        , container::domain
                        > ( boost::cref(a0), boost::cref(a1), _2D(a0,a0) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebspec_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename T::type value_type;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::chebspec_
                                          , container::domain
                                          , A0 const&, A1 const&
                                          , T
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             T  const&) const
    {
      return  boost::proto
            ::make_expr < nt2::tag::chebspec_
                        , container::domain
                        >( boost::cref(a0), boost::cref(a1), T(), _2D(a0,a0) );
    }

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1,nt2::tag::chebspec_,N
                                      , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0&                                     result_type;


    result_type operator()(A0& out, const A1& in) const
    {
      size_t n =  boost::proto::child_c<0>(in);
      size_t k =  boost::proto::child_c<1>(in);

      if (n == 0)
      {
        out.resize(of_size(0, 1));
        return out;
      }

      if(k == 1) ++n;

      out.resize(of_size(n, n));

      compute(out, n, k, N());

      return out;
    }

    private :

    static void compute(A0& out, size_t n, size_t k, boost::mpl::long_<3> const&)
    {
      typedef typename A0::value_type                                   v_type;
      typedef typename meta::as_<v_type>                                t_type;
      chsp<v_type, t_type>(out, n, k);
    }

    static void compute(A0& out, size_t n,  size_t k,  boost::mpl::long_<4> const &)
    {
      typedef typename boost::proto::result_of::child_c<A1&,2>::type       tt_type;
      typedef typename meta::strip<tt_type>::type                         tmp_type;
      typedef typename boost::dispatch::meta::semantic_of<tmp_type>::type   t_type;
      typedef typename t_type::type                                         v_type;
      chsp<v_type, t_type>(out, n, k);
    }

    template < class V, class T >
    static void chsp(A0& c, size_t n,  size_t k)
    {
      typedef container::table<V> tab_t;
      // k = 1 case obtained from k = 0 case with one bigger n.
      --n;
      BOOST_AUTO_TPL(x, nt2::colvect(nt2::cospi(nt2::linspace(Zero<V>(), nt2::One<V>(), n+1))));
      tab_t d = nt2::ones(n+1,1,T());
      d(1) = Two<V>();
      d(n+1) = Two<V>();
      BOOST_AUTO_TPL(c1, mtimes(d, nt2::rowvect(nt2::rec(d))));
      BOOST_AUTO_TPL(c2, nt2::sx(nt2::tag::minus_(), x, nt2::rowvect(x)));
      c = c1/c2;
      //  Now fix diagonal and signs.
      c(1) = (nt2::Two<V>()*nt2::sqr(n)+nt2::One<V>())/nt2::Six<V>();
      for (size_t i=2; i <= n+1;  ++i)
      {
        if(nt2::is_even(i))
        {
          c(_, i) = -c(_, i);
          c(i, _) = -c(i, _);
        }
        if(i <= n)
        {
          c(i,i) = -x(i)/(Two<V>()*(nt2::oneminus(nt2::sqr(x(i)))));
        }
        else
        {
          c(i, i) = -c(1, 1);
        }
      }
      if (k == 1)
      {
        tab_t c1_ = c(nt2::_(2, n+1), nt2::_(2, n+1));
        c = c1_; //ALIASING
      }
    }
  };
} }

#endif
