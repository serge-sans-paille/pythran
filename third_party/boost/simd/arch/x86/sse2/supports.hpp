//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SUPPORTS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SUPPORTS_HPP_INCLUDED

#include <boost/simd/detail/dispatch/detail/declval.hpp>

namespace boost { namespace simd { namespace detail
{
  namespace bd = boost::dispatch;
  namespace tt = nsm::type_traits;

  // Some compilers don't provide _mm_set1_epi64x
  template<typename T> struct support_mm_set1_epi64x
  {
    template<typename U>
    static auto test( int ) -> decltype ( _mm_set1_epi64x(bd::detail::declval<U>())
                                        , tt::true_type()
                                        );

    template<typename>
    static auto test( ... ) -> tt::false_type;

    typedef std::is_same<decltype(test<T>(0)),tt::true_type> type;
  };

  // Some compilers don't provide _mm_set_epi64x
  template<typename T> struct support_mm_set_epi64x
  {
    template<typename U>
    static auto test( int ) -> decltype ( _mm_set_epi64x(bd::detail::declval<U>(),bd::detail::declval<U>())
                                        , tt::true_type()
                                        );

    template<typename>
    static auto test( ... ) -> tt::false_type;

    typedef std::is_same<decltype(test<T>(0)),tt::true_type> type;
  };
} } }

#endif
