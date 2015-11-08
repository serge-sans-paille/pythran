//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_GENERIC_MASK2LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_GENERIC_MASK2LOGICAL_HPP_INCLUDED

#include <boost/simd/boolean/functions/mask2logical.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mask2logical_, tag::cpu_, (A0)
                                    , (generic_< arithmetic_<A0> >)
                                    )
  {
    typedef typename dispatch::meta::call<tag::is_nez_(A0 const&)>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG(assert_is_mask(a0), "Argument to mask2logical is not a valid logical mask");
      return is_nez(a0);
    }
  };
} } }

#endif
