//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_ORTH_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_ORTH_HPP_INCLUDED

#include <nt2/linalg/functions/orth.hpp>
#include <nt2/include/functions/gesvd.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/gt.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/sdk/meta/as_real.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{

template<typename T, typename mat, typename vec>
mat orthr(T const epsi, mat const& u, vec const& s)
{
  size_t r = size_t(sum(if_one_else_zero(gt(s, epsi))(_)));
  return u(_, _(One<size_t>(), r));
}

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::orth_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
    typedef nt2::table<type_t>  result_type;
    typedef nt2::table<rtype_t>  base_type;
    typedef nt2::table<type_t,shape>  matrix_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a) const
    {
      result_type u,v;
      base_type s;
      matrix_type work(a);

      nt2_la_int  m  = nt2::height(work);
      nt2_la_int  n  = nt2::width(work);

      s.resize(nt2::of_size(std::min(m,n), 1));
      u.resize(nt2::of_size(m,m));

      nt2::gesvd( boost::proto::value(work),boost::proto::value(s)
                , boost::proto::value(u),boost::proto::value(v),'A','N');

      rtype_t epsi = nt2::max(m, n)*nt2::eps(s(1));

      return orthr(epsi,u,s);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::orth_, tag::cpu_
                                      ,(A0)(A1)
                                      ,((ast_<A0, nt2::container::domain>))
                                       (scalar_<floating_<A1> > )
                                       )
  {

    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
    typedef nt2::table<type_t> result_type;
    typedef nt2::table<rtype_t>  base_type;
    typedef nt2::table<type_t,shape>  matrix_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const epsi) const
    {
      result_type u,v;
      base_type s;

      matrix_type work(a);
      nt2_la_int  m  = nt2::height(work);
      nt2_la_int  n  = nt2::width(work);

      s.resize(nt2::of_size(std::min(m,n), 1));
      u.resize(nt2::of_size(m,m));

      nt2::gesvd( boost::proto::value(work),boost::proto::value(s)
                , boost::proto::value(u),boost::proto::value(v),'A','N');

      rtype_t epsir = epsi<0 ? nt2::max(m, n)*nt2::eps(s(1)) : epsi;

      return orthr(epsir,u,s);
    }
  };


} }


#endif

