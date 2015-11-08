//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_PERFORM_ALIGNED_ALLOCATION_HPP_INCLUDED
#define BOOST_SIMD_META_PERFORM_ALIGNED_ALLOCATION_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/simd/forward/allocator.hpp>

namespace boost {  namespace simd {  namespace meta
{
  /*!
    @brief Traits detecting aligned allocator

    Detects if a given allocator performs aligned allocation.

    @par Semantic:

    For any @c Allocator @c A :

    @code
    typedef perform_aligned_allocation<A>::type r;
    @endcode

    evaluates to @c boost::mpl::true_ if @c A allocates memory in an aligned
    way adn to @c @c boost::mpl::false_ otherwise

    @tparam Allocator
  **/
  template<typename Allocator>
  struct perform_aligned_allocation : boost::mpl::false_
  {};

  template<typename T>
  struct  perform_aligned_allocation< boost::simd::allocator<T> >
        : boost::mpl::true_
  {};

  template<typename A>
  struct  perform_aligned_allocation<boost::simd::allocator_adaptor<A> >
        : boost::mpl::true_
  {};
} } }

#endif
