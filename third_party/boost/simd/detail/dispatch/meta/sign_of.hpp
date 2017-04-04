//==================================================================================================
/*!
  @file

  Defines the sign_of meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_SIGN_OF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_SIGN_OF_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/primitive_of.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  namespace ext
  {
    template<typename T, typename Enable = void> struct  sign_of
    {
      using primitive = boost::dispatch::primitive_of_t<T>;
      using signed_t  = std::is_signed<primitive>;
      using float_t   = std::is_floating_point<primitive>;
      using type      = typename std::conditional < (signed_t::value || float_t::value)
                                                  , signed
                                                  , unsigned
                                                  >::type;
    };
  }

  /*!
    @ingroup group-introspection
    @brief Return sign of a type

    If a type @c T can contains value with a sign (i.e signed integers and floating points-like
    types), sign_of<T> evaluates to @c signed. Otherwise, it evaluates @c unsigned.

    @tparam T Type to introspect.
  **/
  template<typename T>
  struct sign_of : ext::sign_of<typename std::decay<T>::type>
  {};

  /// Eager shortcut for sign_of
  template<typename T> using sign_of_t = typename sign_of<T>::type;
} }

#endif
