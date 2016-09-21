//==================================================================================================
/*!
  @file

  Defines the pointer_ hierarchy

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_HIERARCHY_POINTER_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_HIERARCHY_POINTER_HPP_INCLUDED

#include <boost/simd/detail/dispatch/adapted/hierarchy/iterator.hpp>
#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>
#include <boost/simd/detail/dispatch/meta/remove_pointers.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief Pointer type hierarchy tag

    Types classified as pointer_ have properties similar to pointer, i.e provides operators
    for dereferencing and pointer arithmetic.

    @tparam T     Base hierarchy
    @tparam Level Number of indirections required to access the pointed value
  **/
  template<typename T, std::size_t Level = 1>
  struct pointer_ : pointer_< typename T::parent, Level >
  {
    using parent = pointer_<typename T::parent, Level>;
  };

  template<typename T>
  struct  pointer_<unspecified_<T>, 1>
        : random_access_iterator_<hierarchy_of_t<typename remove_pointers<T>::type,T>>
  {
    using parent = random_access_iterator_<hierarchy_of_t<typename remove_pointers<T>::type,T>>;
  };

  template<typename T, std::size_t Level>
  struct pointer_<unspecified_<T>, Level> : unspecified_<T>
  {
    using parent = unspecified_<T>;
  };
} }

#endif
