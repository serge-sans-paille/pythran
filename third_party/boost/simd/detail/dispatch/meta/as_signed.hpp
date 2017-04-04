//==================================================================================================
/*!
  @file

  Defines the as_signed meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_AS_SIGNED_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_AS_SIGNED_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/factory_of.hpp>
#include <boost/simd/detail/dispatch/meta/primitive_of.hpp>
#include <boost/simd/detail/dispatch/meta/is_natural.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  namespace detail
  {
    template<typename T, typename Enable = void>
    struct as_signed
    {
      using f_t  = boost::dispatch::factory_of<T>;
      using p_t  = boost::dispatch::primitive_of_t<T>;
      using type = typename f_t::template apply<typename detail::as_signed<p_t>::type>::type;
    };

    template<typename T>
    struct as_signed<T, typename std::enable_if<std::is_fundamental<T>::value>::type>
    {
      template<typename U> struct id { using type = T;};
      using result  = std::conditional<is_natural<T>::value,std::make_signed<T>,id<T>>;
      using type    = typename result::type::type;
    };
  }

  /*!
    @ingroup group-generation
    @brief Turn a type into an equivalent signed type

    Converts any type which Primitive is Fundamental into a compatible signed type.

    @tparam T     Type to convert.
  **/
  template<typename T>
  struct as_signed : detail::as_signed<typename std::decay<T>::type>
  {};

  /// Eager shortcut to as_signed
  template<typename T> using as_signed_t = typename as_signed<T>::type;
} }

#endif
