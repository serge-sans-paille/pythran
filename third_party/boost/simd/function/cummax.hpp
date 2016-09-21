//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CUMMAX_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CUMMAX_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-reduction
    Function object implementing cummax capabilities

    Computes the cumulate maximum of the vector elements

    @par Semantic:

    For every pack parameter of type @c T

    @code
    T r = cummax(x);
    @endcode

    is similar to:

    @code
    T r =x;
    for(int i=0;i < T::static_size; ++i)
      r[i] = max(r[i-1], r[i]);
    @endcode

  **/
  Value cummax(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/cummax.hpp>
#include <boost/simd/function/simd/cummax.hpp>

#endif
