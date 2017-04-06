//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_ALIASING_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_ALIASING_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/simd/detail/nsm.hpp>

#ifndef BOOST_SIMD_NO_STRICT_ALIASING

#ifdef BOOST_MSVC
#define BOOST_SIMD_NO_STRICT_ALIASING
#endif

#ifdef __GNUC__
#define BOOST_SIMD_MAY_ALIAS __attribute__((may_alias))
#endif

#endif

#ifndef BOOST_SIMD_MAY_ALIAS
#define BOOST_SIMD_MAY_ALIAS
#endif

namespace boost { namespace simd { namespace detail
{
  template<typename T, typename Enable = void>
  struct may_alias
  {
    typedef T BOOST_SIMD_MAY_ALIAS type;
  };

  template<typename T>
  struct may_alias<T, typename std::enable_if< std::is_class<T>::value >::type>
  {
    typedef T type;
  };

  template < typename T>
  using  may_alias_t =  typename may_alias<T>::type;
} } }

#endif
