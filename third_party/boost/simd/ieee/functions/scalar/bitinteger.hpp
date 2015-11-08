//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_BITINTEGER_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_BITINTEGER_HPP_INCLUDED

#include <boost/simd/ieee/functions/bitinteger.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/include/functions/scalar/is_positive.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::bitinteger_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return is_positive(a0) ?
            bitwise_cast<result_type, A0>(a0) :
            Signmask<result_type>()-bitwise_cast<result_type, A0>(a0);
    }
  };
} } }


#endif
