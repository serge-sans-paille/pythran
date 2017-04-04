//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXTRACT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-arithmetic

    Random-access extraction of a value subcomponent

    Extract a sub-element of a given value @c v


    @par Header <boost/simd/function/extract.hpp>

    @par Semantic

    For any value @c v of type @c Value and @c o of type @c Offset:

    @code
    auto x = extract(v,o);
    @endcode

    is similar to:

    - If @c v is a scalar value:

      @code
      x = v;
      @endcode

    - If @c v is a SIMD value:

      @code
      x = v[o];
      @endcode

    @param v   Value to extract
    @param o   Position to extract from (offset)

    @return The extracted value
  **/
  template<typename Value, typename Offset>
  scalar_of_t<Value> extract(Value const& v, Offset const& o);
} }
#endif

#include <boost/simd/function/scalar/extract.hpp>
#include <boost/simd/function/simd/extract.hpp>

#endif
