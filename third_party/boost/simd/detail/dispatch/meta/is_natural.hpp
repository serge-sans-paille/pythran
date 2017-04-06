//==================================================================================================
/*!
  @file

  Defines the is_natural meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_IS_NATURAL_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_IS_NATURAL_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-introspection
    @brief Traits for detecting natural integral types

    Checks if a type @c T is a natural integral type, i.e an Integral type able to contain
    natural numbers. This includes all integral types except bool.

    @tparam T Type to check
  **/
  template<typename T>
  using is_natural = nsm::and_< std::is_integral<T>
                                  , nsm::not_<std::is_same<T,bool>>
                                  >;

  /// Eager short-cut for is_native
  template<typename T> using is_natural_t = typename is_natural<T>::type;
} }

#endif
