//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_SX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_SX_HPP_INCLUDED

#include <nt2/core/functions/sx.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/core/utility/max_extent.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sx_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef typename utility::result_of::max_extent<A1, A2>::type ext_t;
    typedef typename meta::call<tag::expand_to_(const A1&, ext_t)>::type t1_t;
    typedef typename meta::call<tag::expand_to_(const A2&, ext_t)>::type t2_t;
    typedef typename meta::call<A0(t1_t, t2_t)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const& a1, A2 const& a2) const
    {
      ext_t s = nt2::utility::max_extent(a1, a2);
      return nt2::functor<A0>()(nt2::expand_to(a1, s), nt2::expand_to(a2, s));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sx_, tag::cpu_,
                              (A0)(A1)(A2)(A3),
                              (unspecified_<A0>)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                            )
  {
    typedef typename utility::result_of::max_extent<A1, A2, A3>::type ext_t;
    typedef typename meta::call<tag::expand_to_(const A1&, ext_t)>::type t1_t;
    typedef typename meta::call<tag::expand_to_(const A2&, ext_t)>::type t2_t;
    typedef typename meta::call<tag::expand_to_(const A3&, ext_t)>::type t3_t;
    typedef typename meta::call<A0(t1_t, t2_t, t3_t)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const& a1,
                                             A2 const& a2, A3 const& a3) const
    {
      ext_t s = nt2::utility::max_extent(a1, a2, a3);
      return nt2::functor<A0>()(nt2::expand_to(a1, s), nt2::expand_to(a2, s), nt2::expand_to(a3, s));
    }
  };
} }

#endif
