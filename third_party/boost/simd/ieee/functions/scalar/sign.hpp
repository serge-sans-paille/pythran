//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_SIGN_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_SIGN_HPP_INCLUDED

#include <boost/simd/ieee/functions/sign.hpp>
#include <boost/simd/include/functions/scalar/is_ltz.hpp>
#include <boost/simd/include/functions/scalar/is_gtz.hpp>
#include <boost/simd/include/functions/scalar/shift_right.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/attributes.hpp>

#ifndef BOOST_SIMD_NO_NANS
#include <boost/simd/include/functions/scalar/is_nan.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sign_, tag::cpu_
                                    , (A0)
                                    , (scalar_< signed_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return shrai(a0, (sizeof(A0)*8-1)) - shrai(-a0, (sizeof(A0)*8-1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sign_, tag::cpu_
                                    , (A0)
                                    , (scalar_< unsigned_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return !!a0;
    }
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sign_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      A0 r = bool(is_gtz(a0))-bool(is_ltz(a0));
      #ifdef BOOST_SIMD_NO_NANS
      return r;
      #else
      return is_nan(a0) ? a0 : r;
      #endif
    }
  };
} } }

#endif
