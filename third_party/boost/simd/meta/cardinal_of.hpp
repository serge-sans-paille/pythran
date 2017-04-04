//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_CARDINAL_OF_HPP_INCLUDED
#define BOOST_SIMD_META_CARDINAL_OF_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/config.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd
{
  namespace tt = nsm::type_traits;
  /*!
    @ingroup group-api

    Computes the register width required to store an instance of any type @c T.

    @par Models:

    @intconst

    @par Semantic:

    For any given cv-qualified type @c T,

    @code
    using r = cardinal_of<T>::type;
    @endcode

    is equivalent to:

    @code
    using r = sd::integral_constant<std::size_t,sizeof(T)/sizeof(boost::dispatch::scalar_of_t<T>)>;
    @endcode

    @tparam T Type which register size is to be computed.

    @see boost::simd::cardinal
  **/
  template<typename T>
  struct  cardinal_of
#if !defined(DOXYGEN_ONLY)
        : tt::integral_constant<std::size_t,1ULL>
#endif
  {};

#if !defined(DOXYGEN_ONLY)
  template<typename T>  struct cardinal_of<T&>                : cardinal_of<T> {};
  template<typename T>  struct cardinal_of<T&&>               : cardinal_of<T> {};
  template<typename T>  struct cardinal_of<T const>           : cardinal_of<T> {};
  template<typename T>  struct cardinal_of<volatile T>        : cardinal_of<T> {};
  template<typename T>  struct cardinal_of<volatile T const>  : cardinal_of<T> {};
#endif

  /*!
    @ingroup group-api
    Eager short-cut for cardinal_of
  **/
  template<typename T>  using cardinal_of_t = typename cardinal_of<T>::type;

  /*!
    @ingroup group-api

    Computes the register size of any given value v.

    @par Semantic:

    For any instance @c v of type @c T,

    @code
    auto r = cardinal(v)
    @endcode

    is equivalent to:

    @code
    auto r = cardinal_of<T>::type{};
    @endcode

    @param v Value which register size is to be computed
    @return An @intconst containing v register size.

    @see boost::simd::cardinal_of
  **/
  template<typename T> BOOST_FORCEINLINE cardinal_of_t<T> cardinal(T&& v) BOOST_NOEXCEPT
  {
    boost::ignore_unused(v);
    return {};
  }
} }

#endif
