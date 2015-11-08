//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_ALGORITHM_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_ALGORITHM_HPP_INCLUDED

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/memory/align_on.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/mpl/assert.hpp>

#include <algorithm>

namespace boost { namespace simd
{
  template<class T, class U, class UnOp>
  U* transform(T const* begin, T const* end, U* out, UnOp f)
  {
    typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
    typedef boost::simd::native<U, BOOST_SIMD_DEFAULT_EXTENSION> vU;

    BOOST_MPL_ASSERT_MSG( vT::static_size == vU::static_size
                        , BOOST_SIMD_TRANSFORM_INPUT_OUTPUT_NOT_SAME_SIZE
                        , (T, U)
                        );

    static const std::size_t N = vU::static_size;

    std::size_t shift = simd::align_on(out, N * sizeof(U)) - out;
    T const* end2 = begin + std::min<size_t>(shift, end-begin);
    T const* end3 = end2 + (end - end2)/N*N;

    // prologue
    for(; begin!=end2; ++begin, ++out)
      *out = f(*begin);

    if(simd::is_aligned(begin, N * sizeof(T)))
    {
      for(; begin!=end3; begin += N, out += N)
        simd::aligned_store(f(simd::aligned_load<vT>(begin)), out);
    }
    else
    {
      for(; begin!=end3; begin += N, out += N)
        simd::aligned_store(f(simd::load<vT>(begin)), out);
    }

    // epilogue
    for(; begin!=end; ++begin, ++out)
      *out = f(*begin);

    return out;
  }

  template<class T1, class T2, class U, class BinOp>
  U* transform(T1 const* begin1, T1 const* end, T2 const* begin2, U* out, BinOp f)
  {
    typedef boost::simd::native<T1, BOOST_SIMD_DEFAULT_EXTENSION> vT1;
    typedef boost::simd::native<T2, BOOST_SIMD_DEFAULT_EXTENSION> vT2;
    typedef boost::simd::native<U, BOOST_SIMD_DEFAULT_EXTENSION> vU;

    BOOST_MPL_ASSERT_MSG( vT1::static_size == vT2::static_size && vT1::static_size == vU::static_size
                        , BOOST_SIMD_TRANSFORM_INPUT_OUTPUT_NOT_SAME_SIZE
                        , (T1, T2, U)
                        );

    static const std::size_t N = vU::static_size;

    std::size_t shift = simd::align_on(out, N * sizeof(U)) - out;
    T1 const* end2 = begin1 + std::min<size_t>(shift, end-begin1);
    T1 const* end3 = end2 + (end - end2)/N*N;

    // prologue
    for(; begin1!=end2; ++begin1, ++begin2, ++out)
      *out = f(*begin1, *begin2);

    if(simd::is_aligned(begin1, N * sizeof(T1)) && simd::is_aligned(begin2, N * sizeof(T2)))
    {
      for(; begin1!=end3; begin1 += N, begin2 += N, out += N)
        simd::aligned_store(f(simd::aligned_load<vT1>(begin1), simd::aligned_load<vT2>(begin2)), out);
    }
    else
    {
      for(; begin1!=end3; begin1 += N, begin2 += N, out += N)
        simd::aligned_store(f(simd::load<vT1>(begin1), simd::load<vT2>(begin2)), out);
    }

    // epilogue
    for(; begin1!=end; ++begin1, ++begin2, ++out)
      *out = f(*begin1, *begin2);

    return out;
  }

  template<class T, class U, class F>
  U accumulate(T const* begin, T const* end, U init, F f)
  {
    typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
    typedef boost::simd::native<U, BOOST_SIMD_DEFAULT_EXTENSION> vU;

    BOOST_MPL_ASSERT_MSG( vT::static_size == vU::static_size
                        , BOOST_SIMD_ACCUMULATE_INPUT_OUTPUT_NOT_SAME_SIZE
                        , (T, U)
                        );

    static const std::size_t N = vT::static_size;

    T const* end2 = simd::align_on(begin, N * sizeof(T));
    T const* end3 = end2 + (end - end2)/N*N;

    vU cur = simd::splat<vU>(init);

    // prologue
    for(; begin!=end2; ++begin)
      init = f(init, *begin);

    for(; begin!=end3; begin += N)
      cur = f(cur, boost::simd::aligned_load<vT>(begin));

    // reduce cur
    for(typename vU::const_iterator b = cur.begin(); b != cur.end(); ++b)
      init = f(init, *b);

    // epilogue
    for(; begin!=end; ++begin)
      init = f(init, *begin);

    return init;
  }
} }

#endif
