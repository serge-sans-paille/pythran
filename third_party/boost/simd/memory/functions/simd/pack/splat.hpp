//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_SPLAT_HPP_INCLUDED

#include <boost/simd/include/functions/splat.hpp>
#include <boost/proto/make_expr.hpp>
#include <boost/proto/traits.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_ , tag::cpu_
                            , (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< ast_<A1, boost::simd::domain> >))
                            )
  {
    typedef typename proto::domain_of<typename A1::type>::type  domain;
    typedef dispatch::meta::
            as_<typename dispatch::meta::
                semantic_of<typename A1::type>::type
               >  value;

    typedef typename proto::result_of::
            make_expr<tag::splat_, domain, const A0&, const value&>::type
    result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const&) const
    {
      return boost::proto::detail::
             make_expr_<tag::splat_, domain, const A0&, const value&>()(a0, value());
    }
  };
} } }

#endif
