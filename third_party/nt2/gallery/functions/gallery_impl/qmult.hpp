//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_QMULT_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_QMULT_HPP_INCLUDED

#include <nt2/gallery/functions/qmult.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/randn.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qmult_, tag::cpu_
                            , (A0)(T)
                            , (scalar_<integer_<A0> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    BOOST_DISPATCH_RETURNS( 2
                          , (A0 const& n, T const & t)
                          , (nt2::qmult(nt2::eye(n, n, t)))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qmult_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 1
                          , (A0 const& n)
                          , (nt2::qmult(nt2::eye(n, n, meta::as_<double>())))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1, nt2::tag::qmult_
                                      , N , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0&                                               result_type;

    BOOST_FORCEINLINE result_type operator()(A0& out, const A1& in) const
    {
      typedef typename  boost::proto::result_of::child_c<A1&,0>
                                    ::value_type::value_type        value_t;

      size_t n = nt2::size(boost::proto::child_c<0>(in), 1);

      nt2::table<value_t> q,r;
      nt2::tie(q,r) = nt2::qr(nt2::randn(n, n, nt2::meta::as_<value_t>()));

      out = nt2::mtimes ( nt2::mtimes ( q
                                      , from_diag(nt2::sign(diag_of(r)))
                                      )
                        , boost::proto::child_c<0>(in)
                        );

      return out;
    }
  };
} }

#endif
