//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_KMS_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_KMS_HPP_INCLUDED

#include <nt2/gallery/functions/kms.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/whereij.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/sdk/meta/value_as.hpp>

namespace nt2 { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<tag::kms_, Domain, 2, Expr>
       : meta::boxed_size<Expr, 1>
  {
  };

  template <class Domain, class Expr>
  struct value_type<tag::kms_, Domain, 2, Expr>
       : meta::value_as<Expr, 0>
  {
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kms_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& n)
                          , ( boost::proto::
                              make_expr<nt2::tag::kms_, container::domain>
                              ( 0.5
                              , nt2::of_size(size_t(n), size_t(n))
                              )
                            )
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kms_, tag::cpu_
                            , (A0)(T)
                            , (scalar_< integer_<A0> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename T::type value_t;
    BOOST_DISPATCH_RETURNS_ARGS ( 2
                                , (A0 const& n, T const& t)
                                , (A0 const& n, T const& )
                                , ( boost::proto::
                                    make_expr<nt2::tag::kms_, container::domain>
                                    ( value_t(0.5)
                                    , nt2::of_size(size_t(n), size_t(n))
                                    )
                                  )
                                )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kms_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)
                              (scalar_< unspecified_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 2, (A0 const& n, A1 const& rho)
                          , ( boost::proto::
                              make_expr<nt2::tag::kms_, container::domain>
                              ( rho
                              , nt2::of_size(size_t(n), size_t(n))
                              )
                            )
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kms_, tag::cpu_
                            , (A0)(A1)(T)
                            , (scalar_< integer_<A0> >)
                              (scalar_< unspecified_<A1> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename T::type value_t;
    BOOST_DISPATCH_RETURNS_ARGS ( 3
                                , (A0 const& n, A1 const& rho, T const& t)
                                , (A0 const& n, A1 const& rho, T const& )
                                , ( boost::proto::
                                    make_expr<nt2::tag::kms_, container::domain>
                                    ( value_t(rho)
                                    , nt2::of_size(size_t(n), size_t(n))
                                    )
                                  )
                                )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::kms_, boost::mpl::long_<2>, nt2::container::domain>))
    )
  {
    typedef A0&                                                         result_type;
    typedef typename A1::value_type                                         value_t;
    typedef typename  meta::is_complex<value_t>::type                      iscplx_t;
    result_type operator()(A0& out, const A1& in) const
    {
      finalize( out
              , boost::proto::value(boost::proto::child_c<1>(in))[0]
              , boost::proto::value(boost::proto::child_c<0>(in))
              , iscplx_t()
              );

      return out;
    }

    private :

    static BOOST_FORCEINLINE
    void finalize ( A0& out, const size_t & n, const value_t & rho
                  , const boost::mpl::false_ &
                  )
    {
      out = nt2::pow( rho
                    , nt2::abs(   nt2::rif(n, meta::as_<value_t>())
                                - nt2::cif(n, meta::as_<value_t>())
                              )
                    );
    }
    static BOOST_FORCEINLINE
    void finalize ( A0& out, const size_t & n, const value_t & rho
                  , const boost::mpl::true_ &
                  )
    {
      out = pow ( rho
                , nt2::abs( nt2::rif(n, meta::as_<value_t>())
                          - nt2::cif(n, meta::as_<value_t>())
                          )
                );

      out = whereij(nt2::functor<nt2::tag::is_less_>(), nt2::conj(out), out);
    }
  };
} }

#endif
