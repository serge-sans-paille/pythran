//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_BROADCAST_HPP_INCLUDED

namespace boost { namespace simd
{
#if defined(DOXYGEN_ONLY)
  /*!
    @ingroup group-swar
    Vector element broadcast

    Return a pack filled with the value of the @c N th value from its argument

    @par Semantic:

    For any value @c v of type @c T and any integral constant @c N

    @code
    T r = broadcast<N>(v);
    @endcode

    is equivalent to:

    @code
    T r = splat<T>(v[N]);
    @endcode

    If @c N is lower than 0 or greater than @c v cardinal,
    then the code is equivalent to:

    @code
    T r = Zero<T>();
    @endcode

    @tparam N index of the value to broadcast
    @param  v register to broadcast value from

    @return A pack filled with the @c N th value of @c x
  **/
  template<typename T, std::size_t N> T broadcast(T const& v) noexcept;
#endif
} }

#include <boost/simd/function/scalar/broadcast.hpp>
#include <boost/simd/function/simd/broadcast.hpp>

#endif
