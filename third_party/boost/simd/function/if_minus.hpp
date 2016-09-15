//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_MINUS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_MINUS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-boolean
    Function object implementing if_minus capabilities

    The function returns the second entry or the difference of the
    second and third entries, according to the first entry being @ref False
    or @ref True

    @par Semantic:

    For every parameters @c c of type @c C and @c x, @c y of type @c T:

    @code
    T1 r = if_minus(c, x, y);
    @endcode

    is similar to:

    @code
    T1 r = c ? x-y : x;
    @endcode
  **/
  Value if_minus(Value const& c, Value const& x, Value const&  y);

  //@overload
  Value if_minus(LogicalValue const& c, Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/if_minus.hpp>
#include <boost/simd/function/simd/if_minus.hpp>

#endif
