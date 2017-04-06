//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_ALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // mask-load from an aligned pointer of int 32
  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer)
                          , bs::avx2_
                          , bd::masked_pointer_<bd::scalar_<bd::ints32_<Pointer>>,tt::true_type>
                          , bd::target_<bs::pack_<bd::ints32_<Target>,bs::avx_>>
                          )
  {
    using target  = typename Target::type;

    BOOST_FORCEINLINE target operator()(Pointer const& p, Target const& ) const
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(p, target::alignment)
                      , "boost::simd::aligned_load was performed on an "
                        "unaligned masked pointer of 32 bits integers"
                      );

      return _mm256_maskload_epi32( (std::int32_t const*)(p.get())
                                  , bs::as_logical_t<target>(p.mask())
                                  );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer)
                          , bs::avx2_
                          , bd::masked_pointer_<bd::scalar_<bd::ints32_<Pointer>>,tt::false_type>
                          , bd::target_<bs::pack_<bd::ints32_<Target>,bs::avx_>>
                          )
  {
    using target  = typename Target::type;

    BOOST_FORCEINLINE target operator()(Pointer const& p, Target const& ) const
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(p, target::alignment)
                      , "boost::simd::aligned_load was performed on an "
                        "unaligned masked pointer of 32 bits integers"
                      );

      auto const& msk = p.mask();
      return  if_else ( bs::as_logical_t<target>(msk)
                      , aligned_load<target>( mask(p.get(),msk) )
                      , target(p.value())
                      );
    }
  };

  //------------------------------------------------------------------------------------------------
  // mask-load from an aligned pointer of int 64
  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer)
                          , bs::avx2_
                          , bd::masked_pointer_<bd::scalar_<bd::ints64_<Pointer>>,tt::true_type>
                          , bd::target_<bs::pack_<bd::ints64_<Target>,bs::avx_>>
                          )
  {
    using target  = typename Target::type;

    BOOST_FORCEINLINE target operator()(Pointer const& p, Target const& ) const
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(p, target::alignment)
                      , "boost::simd::aligned_load was performed on an "
                        "unaligned masked pointer of 64 bits integers"
                      );

      return _mm256_maskload_epi64( (long long int const*)(p.get())
                                  , bs::as_logical_t<target>(p.mask())
                                  );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer)
                          , bs::avx2_
                          , bd::masked_pointer_<bd::scalar_<bd::ints64_<Pointer>>,tt::false_type>
                          , bd::target_<bs::pack_<bd::ints64_<Target>,bs::avx_>>
                          )
  {
    using target  = typename Target::type;

    BOOST_FORCEINLINE target operator()(Pointer const& p, Target const& ) const
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(p, target::alignment)
                      , "boost::simd::aligned_load was performed on an "
                        "unaligned masked pointer of 64 bits integers"
                      );

      auto const& msk = p.mask();
      return  if_else ( bs::as_logical_t<target>(msk)
                      , aligned_load<target>( mask(p.get(),msk) )
                      , target(p.value())
                      );
    }
  };
} } }

#endif
