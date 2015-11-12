//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_BITWISE_AND_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_BITWISE_AND_HPP_INCLUDED

#include <boost/simd/operator/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::bitwise_and_ , tag::cpu_
                                      , (A0)(A1)
                                      , (boost::mpl::
                                              equal_to< boost::mpl::sizeof_<A0>
                                                      , boost::mpl::sizeof_<A1>
                                                      >
                                        )
                                      , (scalar_< arithmetic_<A0> >)
                                        (scalar_< arithmetic_<A1> >)
                                      )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type b_t;
      return bitwise_cast<A0>(b_t(bitwise_cast<b_t>(a0) & bitwise_cast<b_t>(a1)));
    }
  };
} } }

#endif
