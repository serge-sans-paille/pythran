//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RANDSVD_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RANDSVD_HPP_INCLUDED
#include <nt2/gallery/functions/randsvd.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/cumprod.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/randn.hpp>
#include <nt2/include/functions/mnorm.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/qmult.hpp>
#include <nt2/include/functions/bandred.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randsvd_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    typedef typename T::value_type v_t;
    BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const & t), (A0 const& n, T const & ),
                           (nt2::randsvd(n, n, nt2::rec(nt2::Sqrteps<v_t>()), 3, n-1, n-1))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randsvd_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<floating_<A1> > )
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& n, A1 const & kappa),
                           (nt2::randsvd(n, n, kappa, 3, n-1, n-1))
                          )
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randsvd_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    typedef typename T::value_type v_t;
    BOOST_DISPATCH_RETURNS_ARGS(3, (A0 const& m, A0 const& n, T const & t),(A0 const& m, A0 const& n, T const & ),
                           (nt2::randsvd(m, n, nt2::rec(nt2::Sqrteps<v_t>()), 3,
                                         nt2::max(n, m)-1, nt2::max(n, m)-1))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randsvd_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<floating_<A2> > )
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& m, A1 const& n, A2 const & kappa),
                           (nt2::randsvd(m, n, kappa, 3,
                                         nt2::max(n, m)-1, nt2::max(n, m)-1))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randsvd_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<floating_<A1> >)
                              (scalar_<integer_<A2> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& n, A1 const & kappa, A2 const & kl),
                           (nt2::randsvd(n, n, kappa, 3, kl, kl))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randsvd_, tag::cpu_,
                              (A0)(A1)(A2)(A3),
                              (scalar_<integer_<A0> >)
                              (scalar_<floating_<A1> >)
                              (scalar_<integer_<A2> >)
                              (scalar_<integer_<A3> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(4, (A0 const& n, A1 const & kappa, A2 const & mode, A3 const & kl),
                           (nt2::randsvd(n, n, kappa, mode, kl, kl))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randsvd_, tag::cpu_,
                              (A0)(A1)(A2)(A3),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<floating_<A2> >)
                              (scalar_<integer_<A3> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(4, (A0 const& m, A1 const& n, A2 const & kappa, A3 const & mode),
                           (nt2::randsvd(m, n, kappa, mode,
                                         nt2::max(n, m)-1, nt2::max(n, m)-1))
                          )
      };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randsvd_, tag::cpu_,
                              (A0)(A1)(A2)(A3)(A4),
                              (scalar_<integer_<A0> >)
                              (scalar_<floating_<A1> >)
                              (scalar_<integer_<A2> >)
                              (scalar_<integer_<A3> >)
                              (scalar_<integer_<A4> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(5, (A0 const& n, A1 const & kappa, A2 const & mode,
                               A3 const & kl, A4 const & ku),
                           (nt2::randsvd(n, n, kappa, mode, kl, ku))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randsvd_, tag::cpu_,
                              (A0)(A1)(A2)(A3)(A4),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<floating_<A2> >)
                              (scalar_<integer_<A3> >)
                              (scalar_<integer_<A4> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(5, (A0 const& m, A1 const& n, A2 const & kappa,
                               A3 const & mode, A4 const & kl),
                           (nt2::randsvd(m, n, kappa, mode, kl, kl))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randsvd_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<floating_<A2> >)
                              (scalar_<integer_<A3> >)
                              (scalar_<integer_<A4> >)
                              (scalar_<integer_<A5> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(6, ( A0 const& m, A1 const& n, A2 const & kappa
                              , A3 const & mode, A4 const & kl, A5 const & ku
                              )
                          , ( boost::proto::
                              make_expr<nt2::tag::randsvd_, container::domain>
                              ( size_t(m), size_t(n)
                              , kappa, std::ptrdiff_t(mode)
                              , std::size_t(kl), std::size_t(ku)
                              , _2D(m, n)
                              )
                            )
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::randsvd_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,2>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  tmp1_type::value_type                                 value_t;
    typedef nt2::table<value_t>                                               tab_t;
    result_type operator()(A0& out, const A1& in) const
    {
      size_t m = boost::proto::child_c<0>(in);
      size_t n = boost::proto::child_c<1>(in);
      value_t kappa_inv = nt2::rec(boost::proto::child_c<2>(in));
      bool posdef =  kappa_inv < 0;
      kappa_inv = nt2::abs(kappa_inv);


      BOOST_ASSERT_MSG(kappa_inv <= 1, "kappa parameter must be >=  1");
      ptrdiff_t mode =  boost::proto::child_c<3>(in);
      size_t kl = boost::proto::child_c<4>(in);
      size_t ku = boost::proto::child_c<5>(in);
      size_t p  = nt2::min(n, m);
      if (p == 1)
      {
        out = randn(m, n, nt2::meta::as_<value_t>());
        out =  out/nt2::mnorm(out);
        return out;
      }
      tab_t sigma;
      value_t f;
      switch (nt2::abs(mode))
      {
      case 1:
        sigma = nt2::ones(p,1, nt2::meta::as_<value_t>())*kappa_inv;
        sigma(1) = One<value_t>();
        break;
      case 2:
        sigma = nt2::ones(p,1, nt2::meta::as_<value_t>());
        sigma(p) = kappa_inv;
        break;
      case 3:
        f = pow(kappa_inv, nt2::rec(nt2::minusone(value_t(p))));
        sigma = nt2::cumprod(nt2::repnum(f, p, 1))/f;
        break;
      case 4:
        f = (1-kappa_inv)/(p-1);
        sigma =nt2::oneminus(nt2::colvect(nt2::_(nt2::Zero<value_t>(),nt2::minusone(value_t(p))))*f);
        break;
      case 5:
        sigma = nt2::exp(nt2::log(kappa_inv)*
                         nt2::rand(p, 1, nt2::meta::as_<value_t>()));
        break;
      default :
        BOOST_ASSERT_MSG(false, "invalid mode for randsvd");
      }
      if (mode < 0)
      {
        tab_t tmp = nt2::flipud(sigma); //ALIASING
        sigma = tmp;
      }

      tab_t tmp =  nt2::from_diag(sigma); //ALIASING
      sigma = tmp;
      if (posdef)
      {
        tab_t q = nt2::qmult(p, nt2::meta::as_<value_t>());
        out = nt2::mtimes(nt2::mtimes(nt2::transpose(q), sigma), q);
        out = nt2::average(out, nt2::transpose(out));       //ensure matrix is symmetric.
        return out;
      }
      if (m != n)
        sigma = nt2::expand(sigma, m, n); //Expand to m-by-n diagonal matrix.
      if ((kl == 0) && (ku == 0))
      {    // Diagonal matrix requested - nothing more to do.
        out.resize(of_size(m, n));
        out = sigma;
        return out;
      }
      // a = u*sigma*v, where u, v are random orthogonal matrices
      tab_t a = nt2::qmult(nt2::transpose(sigma)); //ALIASING
      sigma = nt2::qmult(nt2::transpose(a));

      if (kl < n-1 || ku < n-1)// Bandwidth reduction.
        out = nt2::bandred(sigma, kl, ku);
      else
        out =  sigma;
      return out;
    }
  };

} }


#endif
