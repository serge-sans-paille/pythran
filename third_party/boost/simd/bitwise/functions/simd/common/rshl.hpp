//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_RSHL_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_RSHL_HPP_INCLUDED

#include <boost/simd/bitwise/functions/rshl.hpp>
#include <boost/simd/include/functions/simd/is_gtz.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/shift_left.hpp>
#include <boost/simd/include/functions/simd/shr.hpp>
#include <boost/simd/include/functions/simd/unary_minus.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/mpl/equal_to.hpp>

#ifndef NDEBUG
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/simd/include/constants/zero.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::rshl_, tag::cpu_, (A0)(A1)(X)
                                       , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                               , boost::simd::meta::cardinal_of<A1>
                                                               >
                                         )
                                       , ((simd_<arithmetic_<A0>,X>))
                                         ((generic_<integer_<A1> >))
                                       )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      #ifndef NDEBUG
      return if_else(is_gtz(a1), shl(a0, max(Zero<A1>(), a1)), shr(a0, max(Zero<A1>(), -a1)));
      #else
      return if_else(is_gtz(a1), shl(a0, a1), shr(a0, -a1));
      #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::rshl_, tag::cpu_, (A0)(A1)(X)
                                       , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                               , boost::simd::meta::cardinal_of<A1>
                                                               >
                                       )
                                       , ((simd_<arithmetic_<A0>,X>))
                                         ((generic_<unsigned_<A1> >))
                                       )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return shl(a0, a1);
    }
  };

} } }

#endif
