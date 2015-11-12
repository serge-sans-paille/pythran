//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_GENERIC_SATURATE_AT_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_GENERIC_SATURATE_AT_HPP_INCLUDED

#include <boost/simd/ieee/functions/saturate_at.hpp>
#include <boost/dispatch/functor/meta/make_functor.hpp>
#include <boost/simd/include/functions/simd/unary_minus.hpp>
#include <boost/simd/include/functions/simd/min.hpp>
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::saturate_at_<Tag>
                                    , tag::cpu_
                                    , (A0)(Tag)
                                    , (generic_<signed_<A0> >)
                                   )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typename dispatch::make_functor<Tag, A0>::type callee;
      const A0 z = callee( dispatch::meta::as_<A0>() );
      return min(z, max(unary_minus(z), a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::saturate_at_<Tag>
                                    , tag::cpu_
                                    , (A0)(Tag)
                                    , (generic_<unsigned_<A0> >)
                                   )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typename dispatch::make_functor<Tag, A0>::type callee;
      return min(a0, callee( dispatch::meta::as_<A0>() ));
    }
  };
} } }

#endif
