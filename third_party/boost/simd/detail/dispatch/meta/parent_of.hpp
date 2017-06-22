//==================================================================================================
/*!
  @file

  Defines the parent_of meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_PARENT_OF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_PARENT_OF_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-introspection
    @brief Parent class retrieval traits

    For any given type @c T , parent_of try to access one of its base class through a
    predefined parent dependent type or specialization. If no such parent class is defined,
    the type computed is @c void itself.

    @tparam T Type to check
  **/
  template<typename T, typename EnableIf = void>
  struct parent_of
  {
    using type = void;
  };

  template<typename T>
  struct parent_of<T, typename boost::enable_if_has_type<typename T::parent>::type>
  {
    using type = typename T::parent;
  };

  /// Eager short-cut for parent_of
  template<typename T> using parent_of_t = typename parent_of<T>::type;
} }

#endif
