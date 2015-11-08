//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_SUCCESSOR_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_SUCCESSOR_HPP_INCLUDED

#include <boost/simd/ieee/functions/successor.hpp>
#include <boost/simd/include/functions/scalar/oneplus.hpp>
#include <boost/simd/include/functions/scalar/adds.hpp>
#include <boost/simd/include/functions/scalar/bitinteger.hpp>
#include <boost/simd/include/functions/scalar/bitfloating.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/simd/include/functions/scalar/is_gez.hpp>
#include <boost/simd/include/functions/scalar/is_nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::successor_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
       return oneplus(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::successor_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if (is_nan(a0)) return a0;
      return bitfloating(oneplus(bitinteger(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::successor_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< integer_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      BOOST_ASSERT_MSG(is_gez(a1), "predecessor rank must be non negative");
      if (Valmax<A0>()-a1 < a0) return Valmax<A0>();
      return a0+a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::successor_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< floating_<A0> >)
                                      (scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG(is_gez(a1), "predecessor rank must be non negative");
      typedef typename dispatch::meta::as_integer<A0, signed>::type itype;
      if (is_nan(a0)) return a0;
      return bitfloating(adds(bitinteger(a0), itype(a1)));
    }
  };
} } }

#endif
