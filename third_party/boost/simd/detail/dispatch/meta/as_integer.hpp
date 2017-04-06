//==================================================================================================
/*!
  @file

  Defines the as_integer meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_AS_INTEGER_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_AS_INTEGER_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/sign_of.hpp>
#include <boost/simd/detail/dispatch/meta/factory_of.hpp>
#include <boost/simd/detail/dispatch/meta/primitive_of.hpp>
#include <boost/simd/detail/dispatch/meta/make_integer.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  namespace detail
  {
    template<typename T, typename Sign> struct as_integer
    {
      using type  = boost::dispatch::make_integer_t < sizeof(boost::dispatch::primitive_of_t<T>)
                                                    , Sign
                                                    , boost::dispatch::factory_of<T>
                                                    >;
    };
  }

  /*!
    @ingroup group-generation
    @brief Turn a type into an equivalent integer

    Converts any type which Primitive is Fundamental into a integral type with a compatible size
    and an optional sign (which by default is the origin type's sign).

    @tparam T     Type to convert.
    @tparam Sign  Optional sign of the resulting integer (@ signed or @c unsigned)
  **/
  template<typename T, typename Sign = boost::dispatch::sign_of_t<T>>
  struct as_integer : detail::as_integer<typename std::decay<T>::type,Sign>
  {};

  template<typename T, typename Sign = boost::dispatch::sign_of_t<T>>
  using as_integer_t = typename as_integer<T,Sign>::type;
} }

#endif
