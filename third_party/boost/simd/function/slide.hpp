//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SLIDE_HPP_INCLUDED

namespace boost { namespace simd
{
#if defined(DOXYGEN_ONLY)
  /*!

  **/
  template<std::size_t N, typename T> T slide(T const& a0, T const& a1) {}

  /// @overload
  template<std::size_t N, typename T> T slide(T const& a0) {}
#endif
} }

#include <boost/simd/function/scalar/slide.hpp>
#include <boost/simd/function/simd/slide.hpp>

#endif
