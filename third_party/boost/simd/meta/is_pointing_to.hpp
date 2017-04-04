//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_META_IS_POINTING_TO_HPP_INCLUDED
#define BOOST_SIMD_META_IS_POINTING_TO_HPP_INCLUDED

#include <boost/pointee.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <iterator>

namespace boost { namespace simd
{
  /*!
    @brief Check for pointer/pointee compatibility

    This meta-function checks if a @c Pointer is actually pointing to a
    value of type @c Pointer.

    @tparam Pointer Pointer type to check
    @tparam Pointee Value type to check
  **/
  template<typename Pointer, typename Pointee>
  struct  is_pointing_to
        : std::is_same< typename std::iterator_traits<Pointer>::value_type
                      , Pointee
                      >
  {};
} }

#endif
