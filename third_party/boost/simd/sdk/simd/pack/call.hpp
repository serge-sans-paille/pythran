//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_CALL_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_CALL_HPP_INCLUDED

#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/proto/make_expr.hpp>

namespace boost { namespace simd { namespace ext
{
  // constants
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(pure_constant_<Func>, tag::formal_
                        , (Func)(A0)
                        , ((target_< ast_<A0, boost::simd::domain> >))
                        )
  {
    typedef typename A0::type::proto_domain domain;

    typedef typename proto::result_of::
            make_expr<Func, domain, const A0&>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      return boost::proto::detail::
             make_expr_<Func, domain, const A0&>()(a0);
    }
  };
} } }

#endif
