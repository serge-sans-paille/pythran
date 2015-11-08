//==============================================================================
//         Copyright 2014               LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2014               LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014               NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_FAST_TOINT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_FAST_TOINT_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/fast_toint.hpp>
#include <boost/simd/include/functions/scalar/toint.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_toint_
                                    , tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, signed> ::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return toint(a0);
    }
  };
} } }

#endif
