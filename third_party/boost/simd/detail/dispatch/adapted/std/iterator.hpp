//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_STD_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_STD_ITERATOR_HPP_INCLUDED

#include <boost/simd/detail/dispatch/adapted/hierarchy/iterator.hpp>
#include <boost/simd/detail/dispatch/meta/value_of.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>
#include <boost/simd/detail/dispatch/detail/is_iterator.hpp>
#include <iterator>

namespace boost { namespace dispatch
{
  namespace ext
  {
    template<typename T>
    struct value_of<T, typename std::enable_if<detail::is_iterator<T>::value>::type>
    {
      using type = typename std::iterator_traits<T>::value_type;
    };

    template<typename T, typename Origin>
    struct hierarchy_of<T,Origin,typename std::enable_if<detail::is_iterator<T>::value>::type>
    {
      using pointee_t  = typename dispatch::value_of<T>::type;
      using category_t = typename std::iterator_traits<T>::iterator_category;
      using type      = iterator_<boost::dispatch::hierarchy_of_t<pointee_t,Origin>, category_t>;
    };
  }
} }

#endif
