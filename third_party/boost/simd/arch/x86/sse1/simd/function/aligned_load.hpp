//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_ALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/slide.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/assert.hpp>

#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4308) // signed/unsigned conversion
#endif

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // load from an aligned pointer of single
  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer)
                          , bs::sse1_
                          , bd::pointer_<bd::scalar_<bd::single_<Pointer>>,1u>
                          , bd::target_<bs::pack_<bd::single_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Pointer p, Target const&) const
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(p, target::alignment)
                      , "boost::simd::aligned_load was performed on an unaligned pointer of float"
                      );

      return _mm_load_ps(p);
    }
  };

  //------------------------------------------------------------------------------------------------
  // load from an aligned pointer of whatever with a misalignment
  BOOST_DISPATCH_OVERLOAD_IF( aligned_load_
                            , (typename Target, typename Pointer, typename Misalignment)
                            , (bs::is_pointing_to<Pointer,typename Target::type::value_type>)
                            , bs::sse1_
                            , bd::pointer_<bd::scalar_<bd::arithmetic_<Pointer>>,1u>
                            , bd::constant_< bd::integer_<Misalignment>>
                            , bd::target_<bs::pack_<bd::arithmetic_<Target>,bs::sse_>>
                            )
  {
    using target  = typename Target::type;
    static const std::size_t                        card = target::static_size;
    static const typename Misalignment::value_type  unalignment = Misalignment::value % card;

    BOOST_FORCEINLINE target operator() ( Pointer p, Misalignment const&, Target const& ) const
    {
      return do_(p, nsm::bool_<unalignment != 0>());
    }

    BOOST_FORCEINLINE target do_( Pointer p, tt::true_type const& ) const
    {
      return slide<unalignment> ( aligned_load<target>( p-unalignment )
                                , aligned_load<target>( p-unalignment+card )
                                );
    }

    BOOST_FORCEINLINE target do_( Pointer p, tt::false_type const& ) const
    {
      return aligned_load<target>(p);
    }
  };
} } }

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif
