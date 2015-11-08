//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_TABLE_ISSORTED_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_TABLE_ISSORTED_HPP_INCLUDED

#include <nt2/predicates/functions/issorted.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/is_ngtz.hpp>
#include <nt2/include/functions/is_nltz.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::issorted_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0) const
    {
      size_t dim =  nt2::firstnonsingleton(a0);
      bool res =  nt2::globalall(is_nltz(diff(a0, dim)));
      return res || nt2::globalall(is_ngtz(diff(a0, dim)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::issorted_, tag::cpu_
                              , (A0)(A1)
                              , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_ < A1> > )
                              )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0, const A1& dim) const
    {
      bool res =  nt2::globalall(is_nltz(diff(a0, dim)));
      return  res || nt2::globalall(is_ngtz(diff(a0, dim)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::issorted_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<bool_<A1> >)
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0, const A1& up) const
    {
      size_t dim =  nt2::firstnonsingleton(a0);
      return issorted(a0, dim, up);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::issorted_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_ < A1> > )
                              (scalar_<bool_<A2> >)
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0, const A1& dim, const A2& up) const
    {
      typedef typename A0::value_type value_type;
      value_type sgn = up ? One<value_type>() : Mone<value_type>();
      return nt2::globalall(is_nltz(diff(a0, dim)*sgn));
    }
  };

} }

#endif
