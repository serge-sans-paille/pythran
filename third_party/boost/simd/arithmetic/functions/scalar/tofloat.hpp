//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_TOFLOAT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_TOFLOAT_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/tofloat.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return static_cast<result_type>(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    #ifdef BOOST_PROTO_STRICT_RESULT_OF
    result_type
    #else
    A0 const&
    #endif
    operator()(A0 const& a0) const
    {
      return a0;
    }
  };
} } }

#endif
