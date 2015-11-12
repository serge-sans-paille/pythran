//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_ITERATE_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_ITERATE_HPP_INCLUDED

#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace details
{
  template<int N, class F>
  struct iterate
  {
    BOOST_FORCEINLINE static void call(F& f)
    {
      iterate<N-1, F>::call(f);
#ifdef BOOST_MSVC
      f.operator()<N-1>();
#else
      f.template operator()<N-1>();
#endif
    }
  };

  template<class F>
  struct iterate<0, F>
  {
    BOOST_FORCEINLINE static void call(F&)
    {
    }
  };
}

namespace meta
{
  template<int N, class F>
  BOOST_FORCEINLINE void iterate(F const& f)
  {
    details::iterate<N, F const>::call(f);
  }

  template<int N, class F>
  BOOST_FORCEINLINE void iterate(F& f)
  {
    details::iterate<N, F>::call(f);
  }
} } }

#endif
