//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MINIMUM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MINIMUM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-reduction
    Function object implementing minimum capabilities

    Returns the least element of the SIMD vector

    @par Semantic:

    For every parameter of type T

    @code
    scalar_of_t<T> r = minimum(x);
    @endcode

    is similar to:

    @code
      scalar_of_t<T> r = Inf;
      for(std::size_t i=0;i<cardinal_of<T>;++i)
        r =  r > x[i] ? x[i] : r;
    @endcode

    @see min, minnummag, minmag

  **/
  scalar_of_t<Value> minimum(Value const & x);
} }
#endif

#include <boost/simd/function/scalar/minimum.hpp>
#include <boost/simd/function/simd/minimum.hpp>

#endif
