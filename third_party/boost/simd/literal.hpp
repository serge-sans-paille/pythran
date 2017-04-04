//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_LITERALS_HPP_INCLUDED
#define BOOST_SIMD_LITERALS_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    // Turn '4' into 4
    constexpr int to_int(char c) { return static_cast<int>(c) - 48; }

    // Terminal case for char recursion
    template< std::size_t N>
    constexpr std::uint64_t parse(int,const char (&)[N], nsm::uint64_t<0> const&)
    {
      return 0;
    }

    // Extract a char, get its value, multiply by current base, repeat
    template< std::size_t N, std::size_t I>
    constexpr std::uint64_t parse(int base, const char (&arr)[N], nsm::uint64_t<I> const&)
    {
      return to_int(arr[I - 1]) * base + parse<N>(base*10, arr,nsm::uint64_t<I-1>{});
    }

    // Intermediate trampoline so MSVC doesn't cry
    template<std::size_t N,char... c> constexpr std::uint64_t parse(int base)
    {
      return parse<N>(base, {c...}, nsm::uint64_t<N>{});
    }
  }

  namespace literal
  {
    // Enables xxx_c to be turned into usable integral constant int_<xxx>
    template <char ...c>
    constexpr nsm::uint64_t< boost::simd::detail::parse<sizeof...(c),c...>(1)> operator"" _c()
    {
      return {};
    }
  }
} }

#endif
