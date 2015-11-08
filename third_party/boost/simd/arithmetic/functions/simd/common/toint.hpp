//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TOINT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TOINT_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/toint.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::toint_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<uint_<A0>,X>))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, signed> ::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return bitwise_cast<result_type>(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::toint_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<int_<A0>,X>))
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
