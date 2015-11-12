//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_KRYLOV_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_KRYLOV_HPP_INCLUDED
#include <nt2/gallery/functions/krylov.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/randn.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/colon.hpp>

namespace nt2 { namespace ext
{
  //
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::krylov_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain >))
                              ((ast_<A1, nt2::container::domain >))
                              (scalar_<integer_<A2> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& a, A1 const& x, A2 const& j),
                           (boost::proto::
                            make_expr<nt2::tag::krylov_, container::domain>
                            (boost::cref(a), boost::cref(x), size_t(j))
                           )
                          )
      };
 NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::krylov_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain >))
                              ((ast_<A1, nt2::container::domain >))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a, A1 const& x),
                           (boost::proto::
                            make_expr<nt2::tag::krylov_, container::domain>
                            (boost::cref(a), boost::cref(x), size(a, 2))
                           )
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::krylov_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain >))
                            )
  {
    typedef typename A0::value_type value_t;
    BOOST_DISPATCH_RETURNS( 1
                          , (A0 const& a)
                          , (boost::proto::
                                make_expr<nt2::tag::krylov_, container::domain>
                                ( a
                                , nt2::ones(size(a, 1), 1,meta::as_<value_t>())
                                , size(a, 1)
                                )
                            )
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::krylov_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& n),
                            ( boost::proto::
                                make_expr<nt2::tag::krylov_, container::domain>
                                ( nt2::randn(n)
                                , nt2::ones(n, 1)
                                , size_t(n)
                                )
                            )
                          )
      };

   NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_ < A1,nt2::tag::krylov_,N
                                        , nt2::container::domain
                                        >
                                ))
                              )
  {
    typedef A0& result_type;

    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_AUTO_TPL(a, boost::proto::child_c<0>(in));
      size_t j =  boost::proto::child_c<2>(in);
      out.resize(nt2::of_size(nt2::size(a, 1), j));
      out(_, 1) = boost::proto::child_c<1>(in);
      for(size_t i=2; i <= j; ++i)
      {
        out(nt2::_, i) = nt2::mtimes(a, out(nt2::_, i-1));
      }
      return out;
    }
  };
} }

#endif
