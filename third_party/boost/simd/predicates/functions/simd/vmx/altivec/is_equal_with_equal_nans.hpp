//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_SIMD_VMX_ALTIVEC_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_SIMD_VMX_ALTIVEC_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/predicates/functions/is_equal_with_equal_nans.hpp>
#include <boost/simd/include/functions/simd/is_greater.hpp>
#include <boost/simd/include/functions/simd/is_equal.hpp>
#include <boost/simd/include/functions/simd/logical_or.hpp>
#include <boost/simd/include/functions/simd/logical_not.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_with_equal_nans_, boost::simd::tag::vmx_, (A0)
                            , ((simd_<floating_<A0>, boost::simd::tag::vmx_>))
                              ((simd_<floating_<A0>, boost::simd::tag::vmx_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return logical_not(logical_or(is_greater(a0, a1), is_greater(a1, a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_with_equal_nans_, boost::simd::tag::vmx_, (A0)
                            , ((simd_<integer_<A0>, boost::simd::tag::vmx_>))
                              ((simd_<integer_<A0>, boost::simd::tag::vmx_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return is_equal(a0, a1);
    }
  };
} } }

#endif
#endif
