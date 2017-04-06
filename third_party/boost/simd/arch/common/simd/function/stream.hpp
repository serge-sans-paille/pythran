//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_STREAM_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_STREAM_HPP_INCLUDED

#include <boost/simd/function/stream.hpp>
#include <boost/simd/function/aligned_store.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - If no stream intrinsic, do a classical store.
  BOOST_DISPATCH_OVERLOAD ( stream_
                          , (typename A0 , typename A1 , typename A2 , typename X)
                          , bs::simd_
                          , bs::pack_<bd::unspecified_<A0>,X>
                          , bd::input_iterator_< bd::scalar_< bd::unspecified_<A1> > >
                          , bd::scalar_< bd::integer_<A2> >
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 a1, A2 const& a2) const
    {
      boost::simd::aligned_store(a0, a1, a2);
    }
  };
} } }

#endif
