//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_BITWISE_SELECT_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_BITWISE_SELECT_HPP_INCLUDED

#include <boost/simd/bitwise/functions/bitwise_select.hpp>
#include <boost/simd/include/functions/simd/bitwise_andnot.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::bitwise_select_, tag::cpu_, (A0)(A1)
                                       , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                               , boost::simd::meta::cardinal_of<A1>
                                                               >
                                          )
                                       , ((generic_<arithmetic_<A0> >))
                                         ((generic_<arithmetic_<A1> >))
                                         ((generic_<arithmetic_<A1> >))
                                       )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A1 const& a2) const
    {
      return bitwise_or(bitwise_and(a1,a0),bitwise_andnot(a2,a0));
    }
  };
} } }

#endif
