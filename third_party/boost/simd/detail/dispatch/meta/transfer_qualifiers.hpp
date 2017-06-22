//==================================================================================================
/*!
  @file

  Defines the meta::transfer_qualifiers meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_TRANSFER_QUALIFIERS_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_TRANSFER_QUALIFIERS_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  namespace detail
  {
    template<typename T, typename U>
    struct transfer_qualifiers { typedef T type; };

    template<typename T, typename U>
    struct transfer_qualifiers<T, U&&> : std::add_rvalue_reference<T> {};

    template<typename T, typename U>
    struct transfer_qualifiers<T, U&> : std::add_lvalue_reference<T> {};

    template<typename T, typename U>
    struct transfer_qualifiers<T, U const> : std::add_const<T> {};

    template<typename T, typename U>
    struct  transfer_qualifiers<T, U const&>
          : std::add_lvalue_reference<typename std::add_const<T>::type>
    {};
  }

  /*!
    @ingroup group-generation
    @brief Transfer qualifiers between types

    Modify a type so it bears the same cref-qualifier than another type while following the
    reference collapsing rules (<a href="http://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers">
    as described in this article</a>) which state that:

    - An rvalue reference to an rvalue reference becomes (“collapses into”) an rvalue reference.
    - All other references to references (i.e., all combinations involving an lvalue reference)
      collapse into an lvalue reference.

    @tparam T Type to modify
    @tparam U Type which modifier needs to be transferred
  **/
  template<typename T, typename U>
  struct transfer_qualifiers : detail::transfer_qualifiers<T,U>
  {};

  /// Eager short-cut for transfer_qualifiers
  template<typename T, typename U>
  using transfer_qualifiers_t = typename transfer_qualifiers<T,U>::type;
} }

#endif
