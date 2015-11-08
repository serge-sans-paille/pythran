//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_ILOGB_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_ILOGB_HPP_INCLUDED
#include <boost/simd/ieee/functions/ilogb.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/scalar/is_gtz.hpp>
#include <boost/simd/include/functions/scalar/exponent.hpp>
#include <boost/simd/sdk/math.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ilogb_, tag::cpu_
                                    , (A0)
                                    , (scalar_< integer_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename boost::dispatch::meta::as_floating<A0>::type type;
      return boost::simd::ilogb(type(a0));
    }
  };

#ifdef BOOST_SIMD_HAS_ILOGB
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ilogb_, tag::cpu_
                                    , (A0)
                                    , (scalar_< double_<A0> >)
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return is_gtz(a0)? ::ilogb(a0) : Zero<result_type>();
    }
  };
#endif

#ifdef BOOST_SIMD_HAS_ILOGBF
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ilogb_, tag::cpu_
                                    , (A0)
                                    , (scalar_< single_<A0> >)
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return is_gtz(a0)? ::ilogbf(a0) : Zero<result_type>();
    }
  };
#endif

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ilogb_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                    )
  {

    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return is_gtz(a0)? boost::simd::exponent(a0) : Zero<result_type>();
    }
  };
} } }


#endif
