//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_CHOW_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_CHOW_HPP_INCLUDED

#include <nt2/gallery/functions/chow.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/toeplitz.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chow_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0> >)
                            )
  {
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::chow_
                                , container::domain
                                , A0 const &, double, double, _2D
                                >::type                        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return  boost::proto::
              make_expr < nt2::tag::chow_
                        , container::domain
                        >( boost::cref(a0), 1.0, 0.0, _2D(a0,a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chow_, tag::cpu_
                            , (A0)(T)
                            , (scalar_<integer_<A0> >)
                              (target_<scalar_<unspecified_<T> > > )
                            )
  {
    typedef typename T::type value_type;
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::chow_
                                , container::domain
                                , A0 const &
                                , value_type, value_type
                                , _2D
                                >::type                        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,T const& ) const
    {
      return  boost::proto
            ::make_expr < nt2::tag::chow_
                        , container::domain
                        > ( boost::cref(a0)
                          , value_type(1), value_type(0)
                          , _2D(a0,a0)
                          );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chow_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<unspecified_<A1> > )
                            )
  {
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::chow_
                                , container::domain
                                , A0 const &
                                , A1, A1
                                , _2D
                                >::type                        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1) const
    {
      return  boost::proto::make_expr < nt2::tag::chow_
                                      , container::domain
                                      > ( boost::cref(a0), boost::cref(a1)
                                        , A1(0), _2D(a0,a0)
                                        );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chow_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<unspecified_<A1> >  )
                              (scalar_<unspecified_<A2> >  )
                            )
  {
    typedef typename  A1::type value_type;
    typedef typename  boost::proto::result_of
                      ::make_expr < nt2::tag::chow_, container::domain
                                  , A0 const &, A1, A1
                                  , _2D
                                  >::type                        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      _2D sizee; sizee[0] = a0; sizee[1] = a0;
      return  boost::proto::make_expr < nt2::tag::chow_
                                      , container::domain
                                      > ( boost::cref(a0)
                                        , boost::cref(a1), cref(a2)
                                        , _2D(a0,a0)
                                        );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::chow_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                     result_type;
    result_type operator()(A0& out, const A1& in) const
    {
      typedef typename A0::value_type value_type;
      out.resize(extent(in));
      typedef typename meta::as_real<value_type>::type r_type;
      typedef typename meta::as_integer<r_type>::type i_type;
      size_t n =  boost::proto::child_c<0>(in);
      value_type alpha =  boost::proto::child_c<1>(in);
      value_type delta = boost::proto::child_c<2>(in);
      BOOST_AUTO_TPL(y2, nt2::zeros(1, n-2, meta::as_<value_type>()));
      BOOST_AUTO_TPL(y1, nt2::cath(alpha, nt2::One<value_type>()));
      BOOST_AUTO_TPL(z2, nt2::cath(y1, y2));
      BOOST_AUTO_TPL(expo, nt2::_(i_type(1), i_type(n)));
      BOOST_AUTO_TPL(z1, nt2::pow(alpha, expo));
      BOOST_AUTO_TPL(z3,  nt2::toeplitz(z1,z2)+delta*nt2::eye(n, nt2::meta::as_<value_type>()));
      return out = z3;
    }
  };
} }


#endif
