//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SORT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SORT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-swar
    Function object implementing sort capabilities

    returns the sorted x vector in ascending order


    @par Header <boost/simd/function/sort.hpp>

    @par Semantic:

    For every parameter of type T

    @code
    T r = sort(x);
    @endcode

  **/
  Value sort(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/sort.hpp>
#include <boost/simd/function/simd/sort.hpp>

#endif
