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
#include <type_traits>

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
  static std::integral_constant<X,X(INT)> value(boost::dispatch::integer_<X> const&);               \
  template<typename X>                                                                              \
  static brigand::single_<FLOAT> value(boost::dispatch::single_<X> const&);                         \
  template<typename X>                                                                              \
  static brigand::double_<DOUBLE> value(boost::dispatch::double_<X> const&);                        \
}                                                                                                   \
/**/

namespace boost { namespace simd { namespace detail
{
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


  template<typename T, bits_t<T> N, bits_t<T> M = 0>
  struct  constantify
  {
    using type = std::integral_constant<T,T(N)>;
  };

  template<bits_t<double> V> struct constantify<double,V>
  {
    using type = brigand::double_<V>;
  };

  template<bits_t<double> V, bits_t<float> W> struct constantify<double,V,W>
  {
    using type = brigand::double_<V>;
  };

  template<bits_t<double> V> struct constantify<float,V>
  {
    using type = brigand::single_<V>;
  };

  template<bits_t<double> V, bits_t<float> W> struct constantify<float,V,W>
  {
    using type = brigand::single_<W>;
  };
} } }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
