//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_BINOMIAL_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_BINOMIAL_HPP_INCLUDED
#include <nt2/gallery/functions/binomial.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/pascal.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/sdk/meta/is_target.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::binomial_, tag::cpu_
                            , (A0)(T)
                            , (scalar_<integer_<A0> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::binomial_
                                          , container::domain
                                          , std::size_t, T, _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, T const& tgt) const
    {
      return  boost::proto::
              make_expr<nt2::tag::binomial_, container::domain>
              ( std::size_t(a0)
              , tgt
              , _2D(a0,a0)
              );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::binomial_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::binomial_
                                          , container::domain
                                          , std::size_t
                                          , meta::as_<double>
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      return  boost::proto::
              make_expr<nt2::tag::binomial_, container::domain>
              ( std::size_t(a0), meta::as_<double>(), _2D(a0,a0) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_<A1,nt2::tag::binomial_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                          result_type;
    typedef typename boost::proto::result_of::child_c<A1&,1>::type            p_type;
    typedef typename meta::strip<p_type>::type                             tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type>::type      t_type;
    typedef typename t_type::type                                         value_type;

    result_type operator()(A0& out, const A1& in) const
    {
      std::size_t n =  boost::proto::child_c<0>(in);
      out.resize(nt2::of_size(n, n));
      nt2::table<value_type, _2D> l = nt2::abs(nt2::pascal(n, 1, nt2::meta::as_<value_type>()));
      nt2::table<value_type, _2D> u = nt2::fliplr(nt2::flipud(l));
      nt2::table<value_type, _2D> d = nt2::from_diag(nt2::pow(value_type(-2), nt2::_(value_type(0), value_type(n-1))));
      out =  nt2::round2even(nt2::mtimes(l, nt2::mtimes(d, u)));
      return out;
    }
  };
} }

#endif
