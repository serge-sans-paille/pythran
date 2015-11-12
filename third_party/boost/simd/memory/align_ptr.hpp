//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGN_PTR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGN_PTR_HPP_INCLUDED

#include <boost/simd/meta/align_ptr.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd
{
  /*!
    @brief Mark pointer as statically aligned

    Apply a static alignment attribute onto an aligned pointer to allow the
    compiler to apply proper optimization on code using this pointer.

    @see meta::align_ptr

    @usage{memory/align_ptr.cpp}

    @param pointer    Aligned pointer to convert.

    @tparam Alignment A power of 2 alignment constraint. By default, this value
                      is equal to BOOST_SIMD_CONFIG_ALIGNMENT.

    @return A pointer equals to the input argument but with compiler-specific
            alignment attribute applied to it.
  **/
  template<std::size_t Alignment, typename T> BOOST_FORCEINLINE
  typename boost::simd::meta::align_ptr<T,Alignment>::type align_ptr(T* pointer)
  {
    BOOST_ASSERT_MSG
    ( boost::simd::is_aligned(pointer,Alignment)
    , "The pointer you try to mark as aligned is not aligned "
      "on the specified alignment in this context"
    );

    return boost::simd::meta::align_ptr<T,Alignment>::value(pointer);
  }

  /// @overload
  template<typename T> BOOST_FORCEINLINE
  typename boost::simd::meta::align_ptr<T>::type align_ptr(T* pointer)
  {
    BOOST_ASSERT_MSG
    ( boost::simd::is_aligned(pointer,BOOST_SIMD_CONFIG_ALIGNMENT)
    , "The pointer you try to mark as aligned is not aligned "
      "on the current SIMD alignment in this context"
    );

    return boost::simd::meta::align_ptr<T>::value(pointer);
  }
} }

#endif
