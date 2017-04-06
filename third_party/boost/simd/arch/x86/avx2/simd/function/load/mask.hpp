//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_LOAD_MASK_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_LOAD_MASK_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/enumerate.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // masked load from a pointer of single AVX
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Pointer, typename Zero)
                          , bs::avx2_
                          , bd::masked_pointer_<bd::scalar_<bd::single_<Pointer>>,Zero>
                          , bd::target_<bs::pack_<bd::single_<Target>,bs::avx_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(Pointer const& p, Target const&) const
    {
      return _mm256_mask_i32gather_ps ( target(p.value()), p.get()
                                      , enumerate<bd::as_integer_t<target>>() // load contiguously
                                      , bs::as_logical_t<target>(p.mask())
                                      , sizeof(float)
                                      );
    }
  };

  //------------------------------------------------------------------------------------------------
  // masked load from a pointer of single SSE
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Pointer, typename Zero)
                          , bs::avx2_
                          , bd::masked_pointer_<bd::scalar_<bd::single_<Pointer>>,Zero>
                          , bd::target_<bs::pack_<bd::single_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(Pointer const& p, Target const&) const
    {
      return _mm_mask_i32gather_ps( target(p.value()), p.get()
                                  , enumerate<bd::as_integer_t<target>>() // load contiguously
                                  , bs::as_logical_t<target>(p.mask())
                                  , sizeof(float)
                                  );
    }
  };

  //------------------------------------------------------------------------------------------------
  // masked load from a pointer of double AVX
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Pointer, typename Zero)
                          , bs::avx2_
                          , bd::masked_pointer_<bd::scalar_<bd::double_<Pointer>>,Zero>
                          , bd::target_<bs::pack_<bd::double_<Target>,bs::avx_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(Pointer const& p, Target const&) const
    {
      return _mm256_mask_i64gather_pd ( target(p.value()), p.get()
                                      , enumerate<bd::as_integer_t<target>>() // load contiguously
                                      , bs::as_logical_t<target>(p.mask())
                                      , sizeof(double)
                                      );
    }
  };

  //------------------------------------------------------------------------------------------------
  // masked load from a pointer of double SSE
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Pointer, typename Zero)
                          , bs::avx2_
                          , bd::masked_pointer_<bd::scalar_<bd::double_<Pointer>>,Zero>
                          , bd::target_<bs::pack_<bd::double_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(Pointer const& p, Target const&) const
    {
      return _mm_mask_i64gather_pd( target(p.value()), p.get()
                                  , enumerate<bd::as_integer_t<target>>() // load contiguously
                                  , bs::as_logical_t<target>(p.mask())
                                  , sizeof(double)
                                  );
    }
  };

  //------------------------------------------------------------------------------------------------
  // masked load from a pointer of 32bits integer AVX
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Pointer, typename Zero)
                          , bs::avx2_
                          , bd::masked_pointer_<bd::scalar_<bd::ints32_<Pointer>>,Zero>
                          , bd::target_<bs::pack_<bd::ints32_<Target>,bs::avx_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(Pointer const& p, Target const&) const
    {
      return _mm256_mask_i32gather_epi32( target(p.value()), (std::int32_t const*)(p.get())
                                        , enumerate<target>() // load contiguously
                                        , bs::as_logical_t<target>(p.mask())
                                        , sizeof(std::int32_t)
                                        );
    }
  };

  //------------------------------------------------------------------------------------------------
  // masked load from a pointer of 32bits integer SSE
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Pointer, typename Zero)
                          , bs::avx2_
                          , bd::masked_pointer_<bd::scalar_<bd::ints32_<Pointer>>,Zero>
                          , bd::target_<bs::pack_<bd::ints32_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(Pointer const& p, Target const&) const
    {
      return _mm_mask_i32gather_epi32 ( target(p.value()), (std::int32_t const*)(p.get())
                                      , enumerate<target>() // load contiguously
                                      , bs::as_logical_t<target>(p.mask())
                                      , sizeof(std::int32_t)
                                      );
    }
  };

  //------------------------------------------------------------------------------------------------
  // masked load from a pointer of 32bits integer AVX
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Pointer, typename Zero)
                          , bs::avx2_
                          , bd::masked_pointer_<bd::scalar_<bd::ints64_<Pointer>>,Zero>
                          , bd::target_<bs::pack_<bd::ints64_<Target>,bs::avx_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(Pointer const& p, Target const&) const
    {
      return _mm256_mask_i64gather_epi64( target(p.value())
                                        , (long long int const*)(p.get())
                                        , enumerate<target>() // load contiguously
                                        , bs::as_logical_t<target>(p.mask())
                                        , sizeof(std::int64_t)
                                        );
    }
  };

  //------------------------------------------------------------------------------------------------
  // masked load from a pointer of 32bits integer SSE
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Pointer, typename Zero)
                          , bs::avx2_
                          , bd::masked_pointer_<bd::scalar_<bd::ints64_<Pointer>>,Zero>
                          , bd::target_<bs::pack_<bd::ints64_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(Pointer const& p, Target const&) const
    {
      return _mm_mask_i64gather_epi64 ( target(p.value()), (long long int const*)(p.get())
                                      , enumerate<target>() // load contiguously
                                      , bs::as_logical_t<target>(p.mask())
                                      , sizeof(std::int64_t)
                                      );
    }
  };
} } }

#endif
