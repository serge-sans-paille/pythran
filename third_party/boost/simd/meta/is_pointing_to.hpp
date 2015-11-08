//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_IS_POINTING_TO_HPP_INCLUDED
#define BOOST_SIMD_META_IS_POINTING_TO_HPP_INCLUDED

#include <boost/pointee.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/meta/is_iterator.hpp>
#include <iterator>

namespace boost { namespace simd { namespace meta
{
  /*!
    @brief Check for pointer/pointee compatibility

    This metafunction checks if a @c Pointer is actually pointing to a
    value of type @c Pointer.

    @tparam Pointer Pointer type to check
    @tparam Pointee Value type to check
  **/
  template<typename Pointer, typename Pointee>
  struct  is_pointing_to
        : boost::is_same< typename std::iterator_traits<Pointer>::value_type
                        , Pointee
                        >
  {};
} } }

#endif
