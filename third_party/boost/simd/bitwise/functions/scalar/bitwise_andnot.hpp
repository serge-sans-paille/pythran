//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_BITWISE_ANDNOT_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_BITWISE_ANDNOT_HPP_INCLUDED

#include <boost/simd/bitwise/functions/bitwise_andnot.hpp>
#include <boost/simd/include/functions/scalar/complement.hpp>
#include <boost/simd/include/functions/scalar/bitwise_and.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::bitwise_andnot_, tag::cpu_, (A0)(A1),
                                        (boost::mpl::bool_<sizeof(A0) == sizeof(A1)>)
                                      , (scalar_< arithmetic_<A0> >)
                                        (scalar_< arithmetic_<A1> >)
                                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type bts;
      return bitwise_cast<A0>(b_and(bitwise_cast<bts>(a0),
                                    b_not(bitwise_cast<bts>(a1))
                                   )
                             );
    }
  };
} } }

#endif
