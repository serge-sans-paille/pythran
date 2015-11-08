//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_INVOL_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_INVOL_HPP_INCLUDED

#include <nt2/gallery/functions/invol.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/uminus.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/hilb.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::invol_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0> > )
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& n),
                           ( nt2::invol(n, nt2::meta::as_<double>()) )
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::invol_, tag::cpu_
                            , (A0)(T)
                            , (scalar_<integer_<A0> >)
                              (target_<scalar_<floating_<T> > >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 2
                          , (A0 const& n, T const& t)
                          , ( boost::proto::make_expr
                              <nt2::tag::invol_, container::domain>
                              ( n, t, nt2::of_size(n, n) )
                            )
                          )

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::invol_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                        result_type;
    typedef typename boost::proto::result_of::child_c<A1&,1>::type        tmp_type;
    typedef typename meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type >::type target_t;
    typedef typename target_t::type                                        value_t;

    result_type operator()(A0& out, const A1& in) const
    {
      size_t n =  boost::proto::child_c<0>(in);
      out.resize(nt2::of_size(n, n));

      out = nt2::hilb(n,target_t());

      value_t d = -value_t(n);
      out(nt2::_, 1) =  d*out(nt2::_, 1); //*= d;

      for (size_t i = 1;  i <= n-1; ++i)
      {
        value_t fac = value_t(n)/i;
        d *= nt2::oneplus(fac)*nt2::oneminus(fac);
        out(i+1, nt2::_) =  d*out(i+1, nt2::_); // *= d;
      }

      return out;
    }
  };
} }

#endif
