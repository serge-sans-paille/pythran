//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_NANASUM2_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_NANASUM2_HPP_INCLUDED

#include <nt2/core/functions/nanasum2.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <nt2/include/constants/nan.hpp>

//TODO include complex cases
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nanasum2_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef typename  meta::call<tag::sqr_abs_(A0 const&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a) const
    {
      return nt2::if_zero_else(nt2::is_nan(a), nt2::sqr_abs(a));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nanasum2_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> > )
                              (scalar_< integer_<A1>  > )
                            )
  {
    typedef typename  meta::call<tag::abs_(A0 const&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const &) const
    {
      return nt2::if_zero_else(nt2::is_nan(a), nt2::sqr_abs(a));
    }
  };
} }

#endif
