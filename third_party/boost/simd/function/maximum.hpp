//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MAXIMUM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MAXIMUM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-reduction
    Function object implementing maximum capabilities

    Returns the greatest element of the SIMD vector

    @par Semantic:

    For every parameter of type T

    @code
    scalar_of_t<T> r = maximum(x);
    @endcode

    is similar to:

    @code
      scalar_of_t<T> r = Minf;
      for(std::size_t i=0;i<cardinal_of<T>;++i)
        r =  r < x[i] ? x[i] : r;
    @endcode

  **/
  scalar_of_t<Value> maximum(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/maximum.hpp>
#include <boost/simd/function/simd/maximum.hpp>

#endif
