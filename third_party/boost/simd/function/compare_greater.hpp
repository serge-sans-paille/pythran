//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COMPARE_GREATER_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COMPARE_GREATER_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-reduction
    Function object implementing compare_greater capabilities

    return a bool that is the result of the lexicographic
    test for > on all elements of the entries

    It is probably not what you wish. Have a look to @ref is_greater

    @par Semantic:

    For every parameters @c x and @c y :

    @code
    bool r = compare_greater(x,y);
    @endcode

    is similar to:

    @code
      bool r = false;
      for(std::size_t i=0;i<cardinal_of<A0>::value;++i)
      {
        if (x[i] > y[i])  {r =  true; break;}
        if (y[i] > x[i])  {r = false; break;}
      }
    @endcode

    @see is_greater
  **/
  bool compare_greater(Value const& v0, Value const& v1);
} }
#endif

#include <boost/simd/function/scalar/compare_greater.hpp>
#include <boost/simd/function/simd/compare_greater.hpp>

#endif
