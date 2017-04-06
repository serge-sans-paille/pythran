//==================================================================================================
/*!
  @file

  Boilerplate code for static loop unrolling

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.

  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ITERATE_HPP_INCLUDED
#define BOOST_SIMD_ITERATE_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>

#include <initializer_list>

namespace boost { namespace simd {
template<typename F, typename... V>
inline void unroll_impl(F&& f, nsm::list<V...> const&)
{
  (void)std::initializer_list<bool>{ (std::forward<F>(f)( V()) ,true)... };
}

template<int N, typename F>
void iterate(F &&f)
{
  unroll_impl( std::forward<F>(f), nsm::range<int, 0, N>{});
}

} }
#endif
