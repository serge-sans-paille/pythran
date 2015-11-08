//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_MCSNE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_MCSNE_HPP_INCLUDED

#include <nt2/linalg/functions/mcsne.hpp>
#include <nt2/include/functions/lange.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/maximum.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/include/constants/eps.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::mcsne_,Domain,N,Expr>
        : meta::size_as<Expr,1>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::mcsne_,Domain,N,Expr>
        : meta::value_as<Expr,1>
  {};
} }

namespace nt2{ namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mcsne_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A0 const& a1),
                           (boost::proto::
                            make_expr<nt2::tag::mcsne_, container::domain>
                            ( boost::cref(a0), boost::cref(a1) )
                           )
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::mcsne_,N,nt2::container::domain>))
                            )
  {
    typedef typename A1::proto_child1::proto_child0::value_type ctype_t;
    typedef typename nt2::meta::as_real<ctype_t>::type   type_t;
    typedef typename boost::dispatch::meta::downgrade<ctype_t>::type dtype;
    typedef typename meta::option<typename  A1::proto_child1::proto_child0::settings_type,nt2::tag::shape_>::type shape;
    typedef nt2::memory::container<tag::table_, ctype_t, nt2::settings(nt2::_2D)> desired_semantic;
    typedef nt2::memory::container<tag::table_, ctype_t, nt2::settings(nt2::_2D,shape)> desired_semantic1;
    typedef A0&                                                          result_type;

     result_type operator()(A0& x, A1& a1) const
    {
      NT2_AS_TERMINAL_IN(desired_semantic1,a,boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_IN(desired_semantic,b,boost::proto::child_c<1>(a1));

      nt2_la_int lda = a.leading_size();
      nt2_la_int na = nt2::width(a);
      nt2_la_int nb = nt2::width(b);
      x.resize(nt2::of_size(na,nb));

      double eps = boost::simd::Eps<double>();
      double anrm = nt2::lange( boost::proto::value(a),'I');
      double cte = anrm*eps*nt2::sqrt( double(na));
      double xnrm, rnrm;

      nt2::container::table<dtype> sa,sx;
      nt2::container::table<ctype_t> e;
      nt2::container::table<dtype,nt2::upper_triangular_> sr,sr1(nt2::of_size(na,na));
      sa = nt2::cast<dtype>(a);
      sr = nt2::qr(sa);

      size_t size_n = sizeof(dtype)*(na);

      for(nt2_la_int i=0; i<na; i++)
      {
        std::memcpy(sr1.raw()+i*na, sr.raw()+i*lda, size_n);
      }

      boost::proto::value(sr).swap(boost::proto::value(sr1) );

      for(nt2_la_int iterb = 1 ; iterb <= nb ; iterb++)
      {
        sx= nt2::mtimes(nt2::trans(sa),nt2::cast<dtype>(b( _ ,iterb) ));

        sx = nt2::linsolve(nt2::trans(sr),sx);
        sx = nt2::linsolve(sr,sx);

        x( _(1,na) ,iterb) = nt2::cast<ctype_t>(sx);

        e = b( _ ,iterb) - nt2::mtimes(a,x( _(1,na) ,iterb));

        for( size_t i = 1; i<=10;++i)
        {
          sx = nt2::cast<dtype> (nt2::mtimes(nt2::trans(a),e) ) ;

          sx = nt2::linsolve(nt2::trans(sr),sx);
          sx = nt2::linsolve(sr,sx);

          e = nt2::cast<ctype_t>(sx);
          rnrm = nt2::maximum(nt2::abs(e(_)));
          x( _(1,na) ,iterb) = x( _(1,na) ,iterb) + e;
          e = b( _ ,iterb) - nt2::mtimes(a,x( _(1,na) ,iterb) );

          xnrm = nt2::maximum(nt2::abs(x( _(1,na) ,iterb) ));

          if(rnrm < xnrm*cte) { break; }
        }
      }
      return x;
    }
  };

} }

#endif
