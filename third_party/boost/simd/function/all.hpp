//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ALL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ALL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
 /*!
    @ingroup group-reduction
    Function object implementing all capabilities

    Returns @ref True if all elements of the input vector are non zero.

    @par Semantic:

    For every parameter of type T

    @code
    bool r = all(x);
    @endcode

    is similar to:

    @code
    bool r = true;
    for(result_type i = 0; i != meta::cardinal_of<T>; ++i)
      if (!x[i]) {r =  false; break; }
    @endcode

  **/
  Value all(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/all.hpp>
#include <boost/simd/function/simd/all.hpp>

#endif
