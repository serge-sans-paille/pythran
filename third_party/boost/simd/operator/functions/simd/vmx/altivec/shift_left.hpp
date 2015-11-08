//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_SHIFT_LEFT_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_SHIFT_LEFT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/operator/functions/shift_left.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shift_left_
                                    , boost::simd::tag::vmx_
                                    , (A0)(A1)
                                    , ((simd_<integer_<A0>,boost::simd::tag::vmx_>))
                                      ((simd_<integer_<A1>,boost::simd::tag::vmx_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_unsigned<A1>::type type;
      BOOST_ASSERT_MSG( assert_good_shift<A0>(a1)
                      , "shift_left: a shift is out of range"
                      );

      return vec_sl(a0(), simd::bitwise_cast<type>(a1)());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shift_left_
                                    , boost::simd::tag::vmx_
                                    , (A0)(A1)
                                    , ((simd_<integer_<A0>,boost::simd::tag::vmx_>))
                                      (scalar_<integer_<A1> >)
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG( assert_good_shift<A0>(a1)
                      , "shift_left: a shift is out of range"
                      );

      return a0 << splat<A0>(a1);
    }
  };
} } }

#endif
#endif
