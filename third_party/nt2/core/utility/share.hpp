//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_SHARE_HPP_INCLUDED
#define NT2_CORE_UTILITY_SHARE_HPP_INCLUDED

/**!
 * @file
 * @brief Defines the \c nt2::share Range adaptor
 **/

#include <iterator>
#include <boost/array.hpp>
#include <nt2/sdk/memory/fixed_allocator.hpp>

namespace nt2
{
  //============================================================================
  /**!
   * @brief Range adaptor for sharing data within Container
   *
   * Convert an ContiguousIterator range into a type suitable to initializing a
   * container using the \c nt2::shared_ settings.
   *
   * @param begin Iterator to the first element of the range to adapt
   * @param end   Iterator to the past-the-end element of the range to adapt
   *
   * @return A \c nt2::memory::fixed_allocator adapting the initial Range.
   *
   * @code
   * std::vector<float> v(16);
   * table<float, shared_> t( share(v.begin(), v.end(), of_size(16) );
   *
   * assert(t(1) == v[0]);
   * @endcode
   *
   * In this example, t will beahve as a regular \c nt2::table but will peruse
   * the memory owned by the \c std::vector \c v. When \c t will go out of scope,
   * no memory will be released by \c t itself.
   *
   * @note Using shared data is an advanced feature and require precise
   * monitoring of actual data life span. More precisely, returning shared data
   * from function while sharing local memory has to be avoided.
   *
   **/
  //============================================================================
  template<class ContiguousIterator>
  memory::fixed_allocator
          < typename std::iterator_traits<ContiguousIterator>::value_type >
  share(ContiguousIterator begin, ContiguousIterator end)
  {
    memory::fixed_allocator
          < typename std::iterator_traits<ContiguousIterator>::value_type >
    that(begin,end);

    return that;
  }

  //============================================================================
  // Overload for static array and boost::array
  // TODO: std::array support
  //============================================================================
  template<class Type, std::size_t Size>
  memory::fixed_allocator<Type>
  share( boost::array<Type,Size>& values)
  {
    memory::fixed_allocator<Type> that(values.begin(),values.end());
    return that;
  }

  template<class Type, std::size_t Size>
  memory::fixed_allocator<Type>
  share( Type (&values)[Size])
  {
    memory::fixed_allocator<Type> that(&values[0], &values[0]+Size);
    return that;
  }
}

#endif
