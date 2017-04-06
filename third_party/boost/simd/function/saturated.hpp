//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SATURATED_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SATURATED_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/decorator.hpp>
#include <boost/simd/detail/dispatch.hpp>

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-decorator

   provides a saturated version of some functors which produce integral typed values on return.

   This is peculiarly interesting in SIMD mode, as unlike scalars types, SIMD @ref pack of
   integers are not promoted  during current arithmetic operations and this increases the
   overflow risks.


    @par Header <boost/simd/function/saturated.hpp>

    @par Semantic

    @code
    T r = saturated_(func)(< func parameters >);
    @endcode
  **/
  template<typename T> auto saturated_(T const& x) {}

} }
#endif

namespace boost { namespace simd
{
  struct saturated_tag : decorator_<saturated_tag>
  {
    using parent = decorator_<saturated_tag>;
  };

  const detail::decorator<saturated_tag> saturated_ = {};
} }

#endif
