//==================================================================================================
/*!
  @file

  Defines the as_unsigned meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_AS_UNSIGNED_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_AS_UNSIGNED_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/factory_of.hpp>
#include <boost/simd/detail/dispatch/meta/primitive_of.hpp>
#include <boost/simd/detail/dispatch/meta/is_natural.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  namespace detail
  {
    template<typename T, typename Enable = void>
    struct as_unsigned
    {
      using f_t  = boost::dispatch::factory_of<T>;
      using p_t  = boost::dispatch::primitive_of_t<T>;
      using type = typename f_t::template apply<typename detail::as_unsigned<p_t>::type>::type;
    };

    template<typename T>
    struct as_unsigned<T, typename std::enable_if<std::is_fundamental<T>::value>::type>
    {
      template<typename U> struct id { using type = T;};
      using result  = std::conditional<is_natural<T>::value,std::make_unsigned<T>,id<T>>;
      using type    = typename result::type::type;
    };
  }

  /*!
    @ingroup group-generation
    @brief Turn a type into an equivalent unsigned type

    Converts any type which Primitive is Fundamental into a compatible unsigned type.

    @tparam T     Type to convert.
  **/
  template<typename T>
  struct as_unsigned : detail::as_unsigned<typename std::decay<T>::type>
  {};

  template<typename T> using as_unsigned_t= typename as_unsigned<T>::type;
} }

#endif
