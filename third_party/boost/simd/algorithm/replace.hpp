//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_REPLACE_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_REPLACE_HPP_INCLUDED

#include <boost/simd/algorithm/transform.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/pack.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Replaces all elements that are equal to old_value with new_value in the range [first, last).

    @param first      Beginning of the range of elements
    @param last       End of the range of elements
    @param old_val    Value to be replaced
    @param new_val    Value to replace with

    @par Requirement

      - @c first, @c last and @c out must be pointer to Vectorizable type.

      - @c new_val and old_val must be a scalar values convertible to  pointee type of first.

    @par Example:

       @snippet replace.cpp replace

    @par possible output:

       @snippet replace.txt replace
  **/
  template<typename T>
  void replace(T * first, T * last, T const & old_val, T const & new_val)
  {
    struct local
    {
      using p_t = boost::simd::pack<T>;

      local(const T & ov, const T & nv) : nv_(nv), ov_(ov), pnv_(nv), pov_(ov) {}

      T   operator()(T    const& x) const { return x == ov_ ? nv_ : x;          }
      p_t operator()(p_t  const& x) const { return if_else(x == pov_, pnv_, x); }

      T nv_, ov_;
      p_t pnv_, pov_;
    };

    boost::simd::transform(first, last, first, local(old_val, new_val));
  }
} }

#endif
