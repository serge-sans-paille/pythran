//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SUM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SUM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-reduction
    Function object implementing sum capabilities

    Returns the sum of the elements of the SIMD vector

    @par Semantic:

    For every parameter of pack type T

    @code
    scalar_of_t<T> r = sum(x);
    @endcode

    is similar to:

    @code
    scalar_of_t<T> r = Zero;
    for(result_type i = 0; i != T::static_size; ++i)
      r += x[i];
    @endcode

  **/
  scalar_of_t<Value> sum(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/sum.hpp>
#include <boost/simd/function/simd/sum.hpp>

#endif
