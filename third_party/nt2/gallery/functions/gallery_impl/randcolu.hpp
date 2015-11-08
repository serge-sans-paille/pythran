//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RANDCOLU_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RANDCOLU_HPP_INCLUDED

#include <nt2/gallery/functions/randcolu.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/dot.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/globalasum2.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/iceil.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/globalnorm2.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/qmult.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/rsqrt.hpp>
#include <nt2/include/functions/signnz.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randcolu_, tag::cpu_
                            , (A0)(A1)(T)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    typedef typename T::type               v_t;
    typedef nt2::table<v_t>              tab_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::randcolu_
                                          , container::domain
                                          , tab_t
                                          , std::size_t, std::size_t
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 n, A1 k, T const& tgt) const
    {
      tab_t x0 = nt2::rand(std::size_t(1), std::size_t(n), tgt);
      v_t   f  = nt2::sqrt(v_t(n))/nt2::globalnorm2(x0);
      x0 *= f;

      return  boost::proto::
              make_expr < nt2::tag::randcolu_
                        , container::domain
                        > ( x0
                          , std::size_t(k), std::size_t(n)
                          , _2D(n,n)
                          );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randcolu_, tag::cpu_
                            , (A0)(T)
                            , (scalar_<integer_<A0> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS ( 2
                                , (A0 const& n, T const & t)
                                , (A0 const& n, T const & )
                                , (nt2::randcolu(n, 0, T()))
                                )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randcolu_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                            )
  {
    typedef typename  A0::value_type value_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::randcolu_
                                          , container::domain
                                          , const A0&
                                          , std::size_t, std::size_t
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& x0, A1 m, A2 k) const
    {
      BOOST_ASSERT_MSG( std::size_t(m) >=  numel(x0)
                      , "m must be greater or equal to numel(x0)"
                      );

      BOOST_ASSERT_MSG( nt2::isvector(x0)
                      , "x must be a vector"
                      );

      BOOST_ASSERT_MSG( nt2::globalall(nt2::is_gtz(x0))
                      , "x elements must be strictly  positive"
                      );

      BOOST_ASSERT_MSG(     nt2::abs(nt2::globalasum2(x0)-value_t(numel(x0)))
                        <=  value_t(100)*nt2::Eps<value_t>()
                      , "x norm must be sqrt(length(x))"
                      );

      return  boost::proto::
              make_expr<nt2::tag::randcolu_, container::domain>
              ( boost::cref(x0)
              , std::size_t(k)
              , std::size_t(m)
              , _2D(m,numel(x0))
              );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randcolu_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& x0,  A1 const & m)
                          , (nt2::randcolu(x0, m, 0))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randcolu_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& x0)
                          , (nt2::randcolu(x0, nt2::numel(x0), 0))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::randcolu_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,0>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  tmp1_type::value_type                                 value_t;
    typedef typename  nt2::meta::as_integer<value_t>::type                  index_t;

    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_AUTO_TPL(x,boost::proto::child_c<0>(in));
      std::size_t k = boost::proto::child_c<1>(in);
      std::size_t m = boost::proto::child_c<2>(in);
      std::size_t n = numel(x);
      BOOST_AUTO_TPL(a, nt2::expand(nt2::from_diag(x), nt2::of_size(m, n)));
      table<value_t> aa;
      if (!k)
      {
        // A = U*A*V where U and V are two random orthogonal matrices.
        aa = nt2::transpose(nt2::qmult(nt2::transpose(qmult(a))));
      }
      else
      {
        aa = a;
      }
      table<value_t> suma = nt2::sum(nt2::sqr(aa));
      do
      {
        nt2::table<ptrdiff_t> y = nt2::find(nt2::lt(suma, nt2::One<value_t>()));
        nt2::table<ptrdiff_t> z = nt2::find(nt2::gt(suma, nt2::One<value_t>()));
        if(nt2::isempty(y) || nt2::isempty(z)) break;
        std::size_t i = y(nt2::iceil(nt2::rand(nt2::meta::as_<value_t>())*nt2::numel(y)));
        std::size_t j = z(nt2::iceil(nt2::rand(nt2::meta::as_<value_t>())*nt2::numel(z)));
        if (i > j) std::swap(i, j);
        value_t aij = nt2::dot(aa(nt2::_, i), aa(nt2::_, j));
        value_t alpha = nt2::sqrt(nt2::sqr(aij)- nt2::minusone(suma(i))*nt2::minusone(suma(j)));
        value_t t1 = (aij + nt2::signnz(aij)*alpha)/nt2::minusone(suma(j));
        value_t t2 =  nt2::oneminus(suma(i))/(nt2::oneminus(suma(j))*t1);
        value_t t = (nt2::rand(nt2::meta::as_<value_t>()) >  Half<value_t>()) ? t1 : t2;
        value_t c =  nt2::rsqrt(nt2::oneplus(nt2::sqr(t))) ;
        value_t s =  t*c ;
        BOOST_AUTO_TPL( ij, nt2::cath(i, j));
        aa(nt2::_,ij) =   nt2::mtimes(aa(nt2::_,ij), nt2::catv(nt2::cath(c, s), nt2::cath(-s, c))) ;
        suma(j) +=  nt2::minusone(suma(i));
        suma(i) = nt2::One<value_t>();
      } while (true);
      out =  aa;
      return out;
    }
  };
} }

#endif
