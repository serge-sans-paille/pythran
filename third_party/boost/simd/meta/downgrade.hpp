//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_DOWNGRADE_HPP_INCLUDED
#define BOOST_SIMD_META_DOWNGRADE_HPP_INCLUDED

#include <boost/simd/detail/dispatch/detail/downgrade.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <cstdint>

namespace boost { namespace simd
{
  /*!
    @ingroup group-api
    For any fundamental type @c T, provides a member typedef @c type which is a type of the same
    category but with a halved size if possible.
    For any composite type @c T, provides a member typedef @c type which is a type of same model
    but with its primitive type replaced by a type of the same category but with a halved size if
    possible.

    @par Example
    @code
    using di32 = boost::simd::downgrade< std::int32_t >::type;
    using dus8 = boost::simd::downgrade< std::int8_t, unsigned >::type;
    using dp32 = boost::simd::downgrade< boost::simd::pack<double> >::type;

    assert(std::is_same<di32,std::int16_t>::value);
    assert(std::is_same<di32,std::uint8_t>::value);
    assert(std::is_same<dp32,boost::simd::pack<float>>::value);
    @endcode

    @tparam T     Type to downgrade
    @tparam Sign  Sign of the downgraded type. Defaults, to signof_t<T>
  **/
  template<typename T,typename Sign = dispatch::sign_of_t<T>>
  struct downgrade
#if !defined(DOXYGEN_ONLY)
        : dispatch::downgrade<T,Sign>
#endif
  {
#if defined(DOXYGEN_ONLY)
    /// Downgraded type derived from @c T
    using type = implementation defined;
#endif
  };

  /*!
    @ingroup group-api
    Eager short-cut to simd::downgrade

    @tparam T     Type to downgrade
    @tparam Sign  Sign of the downgraded type. Defaults, to signof_t<T>
  **/
  template<typename T,typename Sign = dispatch::sign_of_t<T>>
  using downgrade_t = typename simd::downgrade<T,Sign>::type;
} }

#endif
