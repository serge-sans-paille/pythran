//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_SIGNNZ_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_SIGNNZ_HPP_INCLUDED

#include <boost/simd/ieee/functions/signnz.hpp>
#include <boost/simd/include/functions/scalar/bitwise_and.hpp>
#include <boost/simd/include/functions/scalar/bitwise_or.hpp>
#include <boost/simd/include/functions/scalar/is_nan.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::signnz_, tag::cpu_
                                    , (A0)
                                    , (scalar_< signed_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return (a0>>(sizeof(A0)*8-2)) | 1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::signnz_, tag::cpu_
                                    , (A0)
                                    , (scalar_< unsigned_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return One<A0>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::signnz_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      #ifndef BOOST_SIMD_NO_NANS
      return is_nan(a0) ? a0 : b_or(One<A0>(), b_and(Signmask<A0>(), a0));
      #else
      return b_or(One<A0>(), b_and(Signmask<A0>(), a0));
      #endif
    }
  };
} } }

#endif
