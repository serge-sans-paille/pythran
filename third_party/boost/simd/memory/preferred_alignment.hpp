//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_MEMORY_PREFERRED_ALIGNMENT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_PREFERRED_ALIGNMENT_HPP_INCLUDED

#include <boost/simd/pack.hpp>
#include <boost/simd/detail/dispatch/meta/value_of.hpp>
#include <type_traits>

namespace boost { namespace simd
{
  namespace detail
  {
    template< typename T, std::size_t Cardinal
            , bool isArithmetic = std::is_arithmetic<T>::value
            >
    struct preferred_alignment_
    {
      static const std::size_t value = boost::simd::pack<T,Cardinal>::alignment;
    };

    template< typename T,std::size_t Cardinal>
    struct preferred_alignment_<T,Cardinal,false>
    {
      using value_t = boost::dispatch::value_of_t<T>;
      using base_t  = std::conditional< std::is_same<T,value_t>::value
                                      , nsm::size_t<alignof(T)>
                                      , preferred_alignment_<value_t,Cardinal>
                                      >;

      static const std::size_t value = base_t::type::value;
    };

    template<typename T> struct preferred_alignment_<T,0ULL,true>
    {
      static const std::size_t value = boost::simd::pack<T>::alignment;
    };

    template<typename T, std::size_t N, typename ABI, std::size_t Cardinal>
    struct preferred_alignment_<boost::simd::pack<T,N,ABI>, Cardinal, false>
    {
      static const std::size_t card = Cardinal ? Cardinal : N;
      static const std::size_t value = boost::simd::pack<T,card>::alignment;
    };
  }

  /*!
    @ingroup group-api

    Computes the preferred alignment for any type @c T vectorized with a given cardinal @c Cardinal.
    This alignment is computed by the following formula:

      - if @c T is Vectorizable, uses the alignment of a pack<T,Cardinal>
      - if @c T is Vectorized, uses <tt>T::alignment</tt> directly
      - if @c T is not Vectorizable, uses either the preferred alignment of its underlying value type
        (as computed by value_of) or its own natural alignment (as computed by @c alignof)

    If @c Cardinal is unspecified, all computations are performed by assuming th default cardinal
    of current architecture Vectorized types is used.

    @tparam T Type of data to be allocated
    @tparam Cardinal Cardinal of the pack to be used in the allocated memory.
  */
  template<typename T, std::size_t Cardinal = 0ULL>
  struct  preferred_alignment
#if !defined(DOXYGEN_ONLY)
        : nsm::size_t<detail::preferred_alignment_<T,Cardinal>::value>
#endif
  {};
} }
#endif
