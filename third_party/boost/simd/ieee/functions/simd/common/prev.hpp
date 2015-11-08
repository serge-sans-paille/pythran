//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_PREV_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_PREV_HPP_INCLUDED

#include <boost/simd/ieee/functions/prev.hpp>
#include <boost/simd/include/functions/simd/dec.hpp>
#include <boost/simd/include/functions/simd/if_allbits_else.hpp>
#include <boost/simd/include/functions/simd/next.hpp>
#include <boost/simd/include/functions/simd/is_nan.hpp>
#include <boost/simd/include/functions/simd/unary_minus.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::prev_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return dec(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::prev_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return if_nan_else(is_nan(a0), -boost::simd::next(-a0));
    }
  };

} } }

#endif
