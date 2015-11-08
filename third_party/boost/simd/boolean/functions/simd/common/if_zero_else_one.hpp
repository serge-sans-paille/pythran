//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SIMD_COMMON_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SIMD_COMMON_IF_ZERO_ELSE_ONE_HPP_INCLUDED

#include <boost/simd/boolean/functions/if_zero_else_one.hpp>
#include <boost/simd/include/functions/simd/if_zero_else.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_zero_else_one_
                                    , tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_zero_else(a0, One<A0>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_zero_else_one_
                                    , tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<logical_<A0>,X>))
                                    )
  {
    typedef typename A0::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_zero_else(a0, One<result_type>());
    }
  };
} } }

#endif
