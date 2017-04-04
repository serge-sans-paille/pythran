//==================================================================================================
/*!
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_DETAIL_IS_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_DETAIL_IS_ITERATOR_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch/detail/is_pointer.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace dispatch { namespace detail
{
  namespace tt = nsm::type_traits;

  template<typename T, typename EnableIf = void > struct is_iterator : tt::false_type {};

  template<typename T>
  struct is_iterator<T, typename boost::enable_if_has_type<typename T::iterator_category>::type>
       : tt::true_type
  {};
} } }

#endif
