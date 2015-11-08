//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_LO_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_LO_HPP_INCLUDED

#include <boost/simd/bitwise/functions/lo.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/constants/int_splat.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::lo_, tag::cpu_
                                    , (A0)
                                    , (generic_< arithmetic_<A0> >)
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0,unsigned>::type  result_type;
    typedef typename dispatch::meta::scalar_of<result_type>::type   s_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      static const s_t pattern = (s_t(1) << sizeof(s_t)*(CHAR_BIT/2)) - 1;
      return b_and( integral_constant<result_type, pattern>(), a0 );
    }
  };
} } }

#endif
