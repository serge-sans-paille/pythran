//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_INSERT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_INSERT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-arithmetic

   Modify the value of the nth element of a mutable data.


    @par Header <boost/simd/function/insert.hpp>

    @par Semantic

    Depending on the type of its arguments, insert exhibits different semantics.
    For any value @c v of type @c Value, @c d of type @c Data and @c o of
    type @c Offset:

    @code
    insert(d, o, v);
    @endcode

    is equivalent to:

    - If @c Type is a scalar type:

      @code
      d = v;
      @endcode

    - If @c Type is a SIMD type:

      @code
      d[o] = v;
      @endcode

    @param v   Value to insert
    @param o   Position where to insert
    @param d   Data to insert into

    @return void
  **/
  template<typename Value, typename Offset>
  void insert(Data& d, Offset const& o, Value const& v);
} }
#endif

#include <boost/simd/function/scalar/insert.hpp>
#include <boost/simd/function/simd/insert.hpp>

#endif
