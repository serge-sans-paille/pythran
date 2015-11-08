//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_NULL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_NULL_HPP_INCLUDED

#include <nt2/linalg/functions/null.hpp>
#include <nt2/include/functions/gesvd.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/sdk/meta/as_real.hpp>

#include <nt2/core/container/table/table.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::null_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type type_t;
    typedef nt2::table<type_t>  result_type;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;

    typedef nt2::table<rtype_t> rentry_type;
    typedef nt2::table<type_t,shape>  matrix_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a) const
    {
      return null(a, -1.);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::null_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<floating_<A1> > )
                            )
  {
    typedef typename A0::value_type type_t;
    typedef nt2::table<type_t> result_type;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;

    typedef nt2::table<rtype_t>       rentry_type;
    typedef nt2::table<type_t,shape>  matrix_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const epsi) const
    {
      result_type u,v;
      rentry_type s;

      matrix_type work(a);
      nt2_la_int  m  = nt2::height(work);
      nt2_la_int  n  = nt2::width(work);

      s.resize(nt2::of_size(std::min(m,n), 1));
      v.resize(nt2::of_size(n,n));

      nt2::gesvd(boost::proto::value(work),boost::proto::value(s)
                ,boost::proto::value(u),boost::proto::value(v),'N','A');

      rtype_t epsi_ =  epsi < 0 ? length(v)*nt2::Eps<rtype_t>()*s(1) : epsi;

      size_t j = numel(s);
      for(; (j > 0) && (s(j)<= epsi_); j--);
      j++;

      return nt2::fliplr(trans(v(_(j, last_index<1>(v) ), _)));
    }
  };
} }

#endif
