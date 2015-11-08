//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RANDJORTH_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RANDJORTH_HPP_INCLUDED
#include <nt2/gallery/functions/randjorth.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/blkdiag.hpp>
#include <nt2/include/functions/qmult.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/rec.hpp>

#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/colvect.hpp>

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randjorth_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<floating_<A2> >)
                              (scalar_<integer_<A3> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::randjorth_
                                          , container::domain
                                          , A2, std::size_t, _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 p,  A1 q, A2 c, A3 symm) const
    {
      return  boost::proto::
              make_expr<nt2::tag::randjorth_, container::domain>
              ( c, std::size_t(symm), _2D(p,q) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randjorth_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<floating_<A2> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::randjorth_
                                          , container::domain
                                          , A2, std::size_t, _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 p, A1 q, A2 c) const
    {
      return  boost::proto::
              make_expr<nt2::tag::randjorth_, container::domain>
              ( c, std::size_t(0), _2D(p,q) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randjorth_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_<floating_<A2> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::randjorth_
                                          , container::domain
                                          , typename A2::type
                                          , std::size_t
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 p, A1 q, A2) const
    {
      return  boost::proto::
              make_expr < nt2::tag::randjorth_, container::domain>
                        ( nt2::rec(nt2::Sqrteps<typename A2::type>())
                        , std::size_t(0)
                        , _2D(p,q)
                        );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randjorth_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<integer_<A0> >)
                              (target_<floating_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::randjorth_
                                          , container::domain
                                          , typename A1::type, std::size_t, _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& n, A1 const &) const
    {
      std::size_t p = n >> 1;

      return  boost::proto::
              make_expr<nt2::tag::randjorth_, container::domain>
              ( nt2::rec(nt2::Sqrteps<typename A1::type>())
              , std::size_t(0)
              , _2D(p,n-p)
              );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::randjorth_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,0>::type     tmp_type;
    typedef typename  meta::strip<tmp_type>::type                       tmp1_type;
    typedef typename  tmp1_type::value_type                             value_t;
    typedef nt2::table<value_t>                                         tab_t;

    result_type operator()(A0& out, const A1& in) const
    {
      std::size_t p = boost::proto::value(boost::proto::child_c<2>(in))[0];
      std::size_t q = boost::proto::value(boost::proto::child_c<2>(in))[1];
      bool swaped =  (p > q);
      if (swaped) std::swap(p, q);
      value_t cc = boost::proto::value(boost::proto::child_c<0>(in));
      std::size_t symm = boost::proto::value(boost::proto::child_c<1>(in));
      std::size_t n =  p+q;

      BOOST_ASSERT_MSG( cc >= 1
                      , "provided condition number must be greater or equal one"
                      );

      value_t c1 =  nt2::oneplus(cc)/(nt2::Two<value_t>()*nt2::sqrt(cc));
      tab_t c = nt2::catv(c1, nt2::oneplus(nt2::minusone(c1)*nt2::rand(p-1, 1, nt2::meta::as_<value_t>())));
      tab_t s = nt2::sqrt(nt2::minusone(nt2::sqr(c)));
      tab_t a =  nt2::blkdiag(nt2::catv(nt2::cath(nt2::from_diag( c), nt2::from_diag(-s)),
                                        nt2::cath(nt2::from_diag(-s), nt2::from_diag( c))),
                              nt2::eye(q-p, nt2::meta::as_<value_t>()));
      tab_t b(nt2::of_size(n, n));
      if(symm)
      {
        tab_t u =  nt2::blkdiag(nt2::qmult(p, nt2::meta::as_<value_t>()),
                                nt2::qmult(q, nt2::meta::as_<value_t>()));
        b =   nt2::mtimes(nt2::mtimes(u, a), nt2::transpose(u));
        a = nt2::average(b, nt2::transpose(b));
        out = a;
        return out;
      }
      b(nt2::_(1, p),nt2::_)     = nt2::qmult(a(nt2::_(1, p),nt2::_));
      b(nt2::_(p+1, p+q),nt2::_) = nt2::qmult(a(nt2::_(p+1, p+q),nt2::_));
      a =  transpose(b);
      b(nt2::_(1, p),nt2::_)     = nt2::qmult(a(nt2::_(1, p),nt2::_));
      b(nt2::_(p+1, p+q),nt2::_) = nt2::qmult(a(nt2::_(p+1, p+q),nt2::_));
      if(swaped)
      {
        a = b(  nt2::cath( nt2::_(p+1, p+q),  nt2::_(1, p)), _); // Permute to produce J-orthogonal matrix.
        b = a(_,  nt2::cath( nt2::_(p+1, p+q), nt2:: _(1, p)));
      }
      out = b;
      return out;
    }
  };
} }

#endif
