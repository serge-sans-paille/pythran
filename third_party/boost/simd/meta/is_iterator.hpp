//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_IS_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_META_IS_ITERATOR_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch/detail/declval.hpp>

namespace boost { namespace simd
{
  namespace bd = boost::dispatch;
  namespace tt = nsm::type_traits;
  namespace detail
  {
#if defined(BOOST_DISPATCH_USE_INCOMPLETE_STD)
    // This is far from perfect, but we are in a far from perfect situation.
    template <typename T> struct is_iterator_impl
    {
      struct big{ void *p[2];};
      static_assert(sizeof(big) != sizeof(void*), 
                    "This machine is too weird for us.");

      static big test(...);
      template<class It> static typename It::iterator_category* test(It); // Iterator
      template<class It> static void * test(It *); // Pointer

      static const bool value = sizeof(test(bd::detail::declval<T>())) != sizeof(big);
    };
#else
    template <typename T> struct is_iterator_impl
    {
      static tt::false_type test(...);

      template <  typename U
                , typename=typename std::iterator_traits<U>::difference_type
                , typename=typename std::iterator_traits<U>::pointer
                , typename=typename std::iterator_traits<U>::reference
                , typename=typename std::iterator_traits<U>::value_type
                , typename=typename std::iterator_traits<U>::iterator_category
                > static tt::true_type test(U&&);

      static const bool value = std::is_same< decltype(test(bd::detail::declval<T>()))
                                            , tt::true_type
                                            >::value;
    };
#endif
  }

  /*!
    @ingroup  group-api
    @brief    Checks if type is iterator

    For a given type @c Type, checks if said type is a iterator type.

    @tparam Type      Type to check
  **/
  template<typename T>
  struct is_iterator : tt::integral_constant<bool, detail::is_iterator_impl<T>::value>
  {};

  template<typename T>
  using is_iterator_t = typename is_iterator<T>::type;
} }

#endif
