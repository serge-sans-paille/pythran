//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RANDCORR_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RANDCORR_HPP_INCLUDED
#include <nt2/gallery/functions/randcorr.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/dot.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/iceil.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/minusone.hpp>
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

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randcorr_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    typedef typename T::type                                                         v_t;
    typedef nt2::table<v_t>                                                        tab_t;
    typedef typename meta::call<tag::randcorr_(tab_t, size_t, size_t)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& n,
                                             A1 const& k,
                                             T  const&) const
    {
      nt2::table<v_t> x0 =  nt2::rand(size_t(1), size_t(n), T());
      v_t f = v_t(n)/nt2::globalsum(x0);
      x0 *= f;
      return nt2::randcorr(x0, size_t(n), size_t(k));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randcorr_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const & t), (A0 const& n, T const & ),
                           (nt2::randcorr(n, 0, T()))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randcorr_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                            )
  {
    typedef typename  A0::value_type value_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::randcorr_
                                          , container::domain
                                          , const A0&
                                          , std::size_t
                                          , std::size_t
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& x0,  A1 const & m, A2 const & k) const
    {
      BOOST_ASSERT_MSG( size_t(m) >=  numel(x0)
                      , "m must be greater or equal to numel(x0)"
                      );

      BOOST_ASSERT_MSG( nt2::isvector(x0)
                      , "x must be a vector"
                      );

      BOOST_ASSERT_MSG( nt2::globalall(nt2::is_gtz(x0))
                      , "x elements must be strictly  positive"
                      );

      BOOST_ASSERT_MSG(    nt2::abs(nt2::globalsum(x0)-value_t(numel(x0)))
                        <= value_t(100)*nt2::Eps<value_t>()
                      , "x norm must be length(x)"
                      );

      return  boost::proto::
        make_expr<nt2::tag::randcorr_, container::domain>
        ( boost::cref(x0), std::size_t(k), std::size_t(m), _2D(m,numel(x0)) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randcorr_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& x0,  A1 const & m)
                          , (nt2::randcorr(x0, m, 0))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randcorr_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& x0)
                          , (nt2::randcorr(x0, nt2::numel(x0), 0))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::randcorr_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,0>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  tmp1_type::value_type                                 value_t;
    typedef nt2::table<value_t>                                               tab_t;
    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_AUTO_TPL(x,boost::proto::child_c<0>(in));
      size_t k = boost::proto::child_c<1>(in);
      size_t m = boost::proto::child_c<2>(in);
      size_t n = numel(x);
      BOOST_AUTO_TPL(a, nt2::expand(nt2::from_diag(x), nt2::of_size(m, n)));
      tab_t aa;
      if (!k)
      {
        tab_t q = nt2::qmult(n, nt2::meta::as_<value_t>());
        aa = nt2::mtimes(nt2::mtimes(q, a),nt2::transpose(q));//Not exploiting symmetry here.
      }
      else
      {
        aa = a;
      }
      do
      {
        tab_t diaga = nt2::diag_of(aa);
        nt2::table<ptrdiff_t> y = nt2::find(nt2::lt(diaga, nt2::One<value_t>()));
        nt2::table<ptrdiff_t> z = nt2::find(nt2::gt(diaga, nt2::One<value_t>()));
        if(nt2::isempty(y) || nt2::isempty(z)) break;
        size_t i = y(nt2::iceil(nt2::rand(nt2::meta::as_<value_t>())*nt2::numel(y)));
        size_t j = z(nt2::iceil(nt2::rand(nt2::meta::as_<value_t>())*nt2::numel(z)));
        if (i > j) std::swap(i, j);
        value_t aij = aa(i, j);
        value_t alpha = nt2::sqrt(nt2::sqr(aij)- nt2::minusone(diaga(i))*nt2::minusone(diaga(j)));
        value_t t1 = (aij + nt2::signnz(aij)*alpha)/nt2::minusone(diaga(j));
        value_t t2 =  nt2::oneminus(diaga(i))/(nt2::oneminus(diaga(j))*t1);
        value_t t = (nt2::rand(nt2::meta::as_<value_t>()) >  Half<value_t>()) ? t1 : t2;//Choose randomly from the two roots.
        value_t c =  nt2::rsqrt(nt2::oneplus(nt2::sqr(t))) ;
        value_t s =  t*c ;
        BOOST_AUTO_TPL( ij, nt2::cath(i, j));
        BOOST_AUTO_TPL(rot, nt2::catv(nt2::cath(c, s), nt2::cath(-s, c)));
        aa(nt2::_,ij)  =   nt2::mtimes(aa(nt2::_,ij), rot) ;
        aa(ij, nt2::_) =   nt2::mtimes(nt2::transpose(rot), aa(ij, nt2::_));
        aa(i, i) = nt2::One<value_t>();  //Ensure (i,i) element is exactly 1.
      } while (true);
      out =  aa;
      return out;
    }
  };

} }


#endif
