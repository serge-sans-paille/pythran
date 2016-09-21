//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CUMSUM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CUMSUM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-reduction
    Function object implementing cumsum capabilities

    compute the cumulate sum of the vector elements

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = cumsum(x);
    @endcode

    is similar to:

    @code
    T r =x;
    for(int i=0;i < T::static_size; ++i)
      r[i] += r[i-1];
    @endcode

  **/
  Value cumsum(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/cumsum.hpp>
#include <boost/simd/function/simd/cumsum.hpp>

#endif
