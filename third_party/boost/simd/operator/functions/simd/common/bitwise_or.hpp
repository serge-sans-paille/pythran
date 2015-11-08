//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_BITWISE_OR_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_BITWISE_OR_HPP_INCLUDED

#include <boost/simd/operator/functions/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::bitwise_or_, tag::cpu_
                                       , (A0)(A1)(X)
                                       , (boost::mpl::not_< boost::is_same<A0, A1> >)
                                       , ((simd_<arithmetic_<A0>,X>))
                                         ((simd_<arithmetic_<A1>,X>))
                                       )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return bitwise_or(a0, simd::bitwise_cast<A0>(a1));
    }
  };
} } }

#endif
