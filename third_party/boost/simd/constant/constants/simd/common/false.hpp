//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SIMD_COMMON_FALSE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SIMD_COMMON_FALSE_HPP_INCLUDED

#include <boost/simd/constant/constants/false.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::False, tag::cpu_, (A0)(X)
                                    , ((target_< simd_< logical_<A0>,X> >))
                                    )
  {
    typedef typename A0::type                                       result_type;
    typedef typename result_type::value_type::value_type            base_type;
    typedef typename result_type::template rebind<base_type>::type  target_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return bitwise_cast<result_type>(Zero<target_type>());
    }
  };
} } }

#endif
