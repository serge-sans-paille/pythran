//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_BITWISE_NOTOR_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_BITWISE_NOTOR_HPP_INCLUDED

#include <boost/simd/bitwise/functions/bitwise_notor.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/complement.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_notor_
                                   , tag::cpu_, (A0)(X)
                                   , ((simd_<arithmetic_<A0>,X>))
                                     ((simd_<arithmetic_<A0>,X>))
                                   )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return bitwise_or(complement(a0), a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::bitwise_notor_
                                       , tag::cpu_, (A0)(A1)(X)
                                       , (boost::mpl::not_ < is_same<A0, A1> >)
                                       , ((simd_<arithmetic_<A0>,X>))
                                         ((simd_<arithmetic_<A1>,X>))
                                       )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return bitwise_notor(a0, bitwise_cast<A0>(a1));
    }
  };
} } }

#endif
