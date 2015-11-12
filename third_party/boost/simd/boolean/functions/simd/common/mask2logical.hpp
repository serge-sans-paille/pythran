//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SIMD_COMMON_MASK2LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SIMD_COMMON_MASK2LOGICAL_HPP_INCLUDED

#include <boost/simd/boolean/functions/mask2logical.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/simd/meta/is_logical_mask.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::mask2logical_, tag::cpu_, (A0)(X)
                            , (boost::simd::meta::is_logical_mask<typename simd::meta::as_logical<A0>::type>)
                            , ((simd_< arithmetic_<A0>, X >))
                            )
  {
    typedef typename meta::as_logical<A0>::type ltype;
    typedef typename dispatch::meta::call<tag::bitwise_cast_(A0 const&, dispatch::meta::as_<ltype>)>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG(assert_is_mask(a0), "Argument to mask2logical is not a valid logical mask");
      return bitwise_cast<ltype>(a0);
    }
  };
} } }

#endif
