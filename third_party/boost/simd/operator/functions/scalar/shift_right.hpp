//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_SHIFT_RIGHT_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_SHIFT_RIGHT_HPP_INCLUDED

#include <boost/simd/operator/functions/shift_right.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shift_right_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< floating_<A0> >)(scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type itype;
      return bitwise_cast<result_type>(shift_right(bitwise_cast<itype>(a0),a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shift_right_ , tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< integer_<A0> >)
                                      (scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG( assert_good_shift<A0>(a1)
                      , "shift_right: a shift is out of range"
                      );

      return a0 >> a1;
    }
  };
} } }

#endif
