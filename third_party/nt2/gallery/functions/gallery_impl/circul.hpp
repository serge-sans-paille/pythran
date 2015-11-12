//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_CIRCUL_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_CIRCUL_HPP_INCLUDED

#include <nt2/gallery/functions/circul.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/toeplitz.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::circul_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 1
                          , (A0 const& a0)
                          , ( boost::proto::make_expr
                              < nt2::tag::circul_
                              , container::domain
                              >( nt2::_(A0(1), a0), _2D(a0,a0))
                            )
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::circul_, tag::cpu_
                            , (A0)(T)
                            , (scalar_<integer_<A0> >)
                              (target_<scalar_<unspecified_<T> > > )
                            )
  {
    typedef typename  T::type value_type;

    BOOST_DISPATCH_RETURNS_ARGS ( 2
                                , (A0 const& a0, T const& tgt)
                                , (A0 const& a0, T const& )
                                , ( boost::proto::make_expr
                                    < nt2::tag::circul_
                                    , container::domain
                                    >( nt2::_(value_type(1), value_type(a0))
                                      , _2D(a0,a0)
                                      )
                                  )
                                );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::circul_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain >))
                            )
  {
    BOOST_DISPATCH_RETURNS( 1
                          , (A0 const& a0)
                          , ( boost::proto::make_expr
                              < nt2::tag::circul_
                              , container::domain
                              > ( boost::cref(a0)
                                , _2D(nt2::numel(a0),nt2::numel(a0))
                                )
                            )
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::circul_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                     result_type;
    result_type operator()(A0& out, const A1& in) const
    {
      out.resize(extent(in));
      BOOST_AUTO_TPL( v, nt2::rowvect(boost::proto::child_c<0>(in)));
      BOOST_AUTO_TPL( idx, nt2::_(ptrdiff_t(nt2::numel(v)), ptrdiff_t(-1), ptrdiff_t(2)));
      BOOST_AUTO_TPL( vr, nt2::cath(v(1), v(1, idx)));
      out =  nt2::toeplitz(vr, v);
      return out;
    }
  };
} }

#endif
