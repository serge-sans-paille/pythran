//==================================================================================================
/*!
  @file

  Defines the iterator_ based hierarchies

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_HIERARCHY_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_HIERARCHY_ITERATOR_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>
#include <boost/simd/detail/dispatch/meta/parent_of.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>
#include <iterator>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief Iterator type hierarchy tag

    Types classified as iterator_ model any standard Iterator concepts.

    @tparam T         Base hierarchy
    @tparam Category  Iterator category
  **/
  template<typename T, typename Category>
  struct  iterator_
        : iterator_<typename T::parent, Category>
  {
    using parent = iterator_<typename T::parent, Category>;
  };

  // when type hierarchy is exhausted, run up on the Category
  template<typename T, typename Category>
  struct  iterator_<unspecified_<T>, Category>
        : iterator_ < hierarchy_of_t<typename std::iterator_traits<T>::value_type,T>
                    , parent_of_t<Category>
                    >
  {
    using parent =  iterator_ < hierarchy_of_t<typename std::iterator_traits<T>::value_type,T>
                              , parent_of_t<Category>
                              >;
  };

  // when Category exhausts, goto unspecified_
  template<typename T>
  struct  iterator_<unspecified_<T>, void> : unspecified_<T>
  {
    using parent = unspecified_<T>;
  };

  /*!
    @ingroup group-tag
    @brief Input iterator type hierarchy tag

    Types classified as iterator_ model the standard InputIterator concepts.

    @tparam T         Base hierarchy
  **/
  template<typename T>
  using input_iterator_ = iterator_<T,std::input_iterator_tag>;

  /*!
    @ingroup group-tag
    @brief Output iterator type hierarchy tag

    Types classified as iterator_ model the standard OutputIterator concepts.

    @tparam T         Base hierarchy
  **/
  template<typename T>
  using output_iterator_ = iterator_<T,std::output_iterator_tag>;

  /*!
    @ingroup group-tag
    @brief Forward iterator type hierarchy tag

    Types classified as iterator_ model the standard ForwardIterator concepts.

    @tparam T         Base hierarchy
  **/
  template<typename T>
  using forward_iterator_ = iterator_<T,std::forward_iterator_tag>;

  /*!
    @ingroup group-tag
    @brief Bidirectional iterator type hierarchy tag

    Types classified as iterator_ model the standard BidirectionalIterator concepts.

    @tparam T         Base hierarchy
  **/
  template<typename T>
  using bidirectional_iterator_ = iterator_<T,std::bidirectional_iterator_tag>;

  /*!
    @ingroup group-tag
    @brief Random Access iterator type hierarchy tag

    Types classified as iterator_ model the standard RandomAccessIterator concepts.

    @tparam T         Base hierarchy
  **/
  template<typename T>
  using random_access_iterator_ = iterator_<T,std::random_access_iterator_tag>;

  //------------------------------------------------------------------------------------------------
  // Specialize parent_of so iterator tag hierarchy is reproduced
  //------------------------------------------------------------------------------------------------
  template<> struct parent_of<std::forward_iterator_tag>
  {
    using type = std::input_iterator_tag;
  };

  template<>
  struct parent_of<std::bidirectional_iterator_tag>
  {
    using type = std::forward_iterator_tag;
  };

  template<>
  struct parent_of<std::random_access_iterator_tag>
  {
    using type = std::bidirectional_iterator_tag;
  };
} }

#endif
