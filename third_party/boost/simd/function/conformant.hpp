//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CONFORMANT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CONFORMANT_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/decorator.hpp>
#include <boost/simd/detail/dispatch.hpp>

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-decorator

    The `conformant_` decorator is kind-of associated to std_ if it is available it gives a (perhaps)
    slower version of the involved functor algorithm, but that is fully conformant to the standard
    libc++ (scalar) requirements.

    Up to now only @ref min and @max can use the conformant_ decorator to avoid @ref Nan related corner
    cases on some  architectures as vmx.. or some compilers as gcc whose behaviour is version number
    dependent.

    @par Semantic

    @code
    T r = conformant_(func)(< func parameters >);
    @endcode

  **/
  template<typename T> auto conformant_(T const& x) {}

} }
#endif

namespace boost { namespace simd
{
  struct conformant_tag : decorator_<conformant_tag>
  {
    using parent = decorator_<conformant_tag>;
  };

  const detail::decorator<conformant_tag> conformant_ = {};
} }

#endif
