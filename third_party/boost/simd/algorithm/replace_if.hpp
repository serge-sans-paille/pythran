//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_REPLACE_IF_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_REPLACE_IF_HPP_INCLUDED

#include <boost/simd/algorithm/transform.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/pack.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Replaces all elements  for which predicate p returns true
    by new_value in the range [first, last).

    @param first   Beginning of the range of elements
    @param last    End of the range of elements
    @param p       unary predicate which returns @c true if the element value should be replaced.
    @param new_val Replacement value

    @par Requirement

      - @c first, @c last and @c out must be pointer to Vectorizable type.

      - @c new_val must be a scalar value convertible to  pointee type of first.

    @par Example:

       @snippet replace_if.cpp replace_if

    @par possible output:

       @snippet replace_if.txt replace_if

  **/

  template<typename T, typename P>
  void replace_if(T * first, T * last, P const& p, T const & new_val)
  {
    struct local
    {
      using p_t = pack<T>;

      local(P const& p, const T & nv) : p_(p), nv_(nv), pnv_(nv) {}

      T   operator()(T    const& x  ) const { return p_(x) ? nv_ : x;         }
      p_t operator()(p_t  const& x  ) const { return if_else(p_(x), pnv_, x); }

      P p_;
      T nv_;
      p_t pnv_;
    };

    boost::simd::transform(first, last, first, local(p, new_val));
  }

} }

#endif
