//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_TRAITS_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_TRAITS_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/property_of.hpp>
#include <boost/simd/detail/dispatch/hierarchy.hpp>
#include <boost/config.hpp>
#include <boost/simd/detail/nsm.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4310) // Truncation
#pragma warning(disable: 4309) // Truncation
#endif

/*!

**/
#define BOOST_SIMD_REGISTER_CONSTANT(INT,FLOAT,DOUBLE)                                              \
struct value_map                                                                                    \
{                                                                                                   \
  template<typename X>                                                                              \
  static nsm::type_traits::integral_constant<X,X(INT)> value(boost::dispatch::integer_<X> const&); \
  template<typename X>                                                                              \
  static nsm::single_<FLOAT> value(boost::dispatch::single_<X> const&);                         \
  template<typename X>                                                                              \
  static nsm::double_<DOUBLE> value(boost::dispatch::double_<X> const&);                        \
}                                                                                                   \
/**/

namespace boost { namespace simd { namespace detail
{
  namespace tt = nsm::type_traits;

  template<typename Tag, typename T>
  struct constant_traits
  {
    using key  = boost::dispatch::property_of_t<boost::dispatch::scalar_of_t<T>>;
    using base = typename Tag::value_map;
    using type = decltype( base::value(key()) );
  };

  template<typename RealType, std::intmax_t N, std::intmax_t D = 1> struct ratio {};

  template<typename T>
  using bits_t = typename std::conditional< std::is_integral<T>::value && std::is_signed<T>::value
                                          , std::intmax_t
                                          , std::uintmax_t
                                          >::type;


  template<typename T, std::uintmax_t N, std::uintmax_t M = 0>
  struct  constantify
  {
    using type = tt::integral_constant<T,T(N)>;
  };

  template<std::uintmax_t V> struct constantify<double,V>
  {
    using type = nsm::double_<V>;
  };

  template<std::uintmax_t V, std::uintmax_t W> struct constantify<double,V,W>
  {
    using type = nsm::double_<V>;
  };

  template<std::uintmax_t V> struct constantify<float,V>
  {
    using type = nsm::single_<V>;
  };

  template<std::uintmax_t V, std::uintmax_t W> struct constantify<float,V,W>
  {
    using type = nsm::single_<W>;
  };
} } }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
