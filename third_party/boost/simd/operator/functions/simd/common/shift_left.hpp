//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_SHIFT_LEFT_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_SHIFT_LEFT_HPP_INCLUDED

#include <boost/simd/operator/functions/shift_right.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shift_left_, tag::cpu_
                                   , (A0)(A1)(X)
                                   , ((simd_<floating_<A0>,X>))
                                     ((generic_<integer_<A1> >))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type int_type;
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_left: a shift is out of range");

      return bitwise_cast<result_type>( bitwise_cast<int_type>(a0) << a1 );
    }
  };

} } }

#endif
