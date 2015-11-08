//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SIMD_COMMON_IF_ELSE_ZERO_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SIMD_COMMON_IF_ELSE_ZERO_HPP_INCLUDED

#include <boost/simd/boolean/functions/if_else_zero.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/is_bitwise_logical.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::if_else_zero_, tag::cpu_, (A0)(A1)(X)
                                       , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                               , boost::simd::meta::cardinal_of<A1>
                                                               >
                                         )
                                       , ((simd_<fundamental_<A0>,X>))
                                         ((simd_<arithmetic_<A1>,X>))
                                       )
  {
    typedef A1 result_type;

    template<class A0_>
    typename enable_if< meta::is_bitwise_logical<A0_>, result_type>::type
    BOOST_FORCEINLINE operator()(A0_ const& a0, A1 const& a1) const
    {
      return bitwise_and(a1, genmask(a0));
    }

    template<class A0_>
    typename disable_if< meta::is_bitwise_logical<A0_>, result_type>::type
    BOOST_FORCEINLINE operator()(A0_ const& a0, A1 const& a1) const
    {
      return if_else(a0, a1, Zero<A1>());
    }
  };
} } }

#endif
