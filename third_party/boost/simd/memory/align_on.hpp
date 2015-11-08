//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//         Copyright 2013          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGN_ON_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGN_ON_HPP_INCLUDED

#include <boost/simd/meta/align_ptr.hpp>
#include <boost/simd/memory/align_ptr.hpp>
#include <boost/simd/preprocessor/parameters.hpp>
#include <boost/simd/memory/is_power_of_2.hpp>

#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>
#include <cstddef>

namespace boost { namespace simd
{
  /*!
    @brief Align value or pointer on an arbitrary alignment boundary and
           return the next aligned value or pointer.

    Force the alignment of an  integral value or pointer @c value
    on an arbitrary power of two boundary @c align.

    @par Semantic:

    For any integral power of two alignment boundary @c a and any integral
    value @c v

    @code
    auto r = align_on(v,a);
    @endcode

    is such that

    @code
    bool b = is_aligned(r,a);
    @endcode

    evaluates to @c true.

    For any integral power of two alignment boundary @c a and any pointer @c p
    referencing element of type @c T:

    @code
    auto r = align_on(p,a);
    @endcode

    is equivalent to:

    @code
    auto r = reinterpret_cast<T*>(align_on(reinterpret_cast<size_t>(p),a));
    @endcode

    @usage_output{memory/align_on.cpp, memory/align_on.out}

    @param value Value or pointer to align
    @param align Integral power of two alignment boundary.

    @return The aligned integral value or pointer
  **/
  BOOST_FORCEINLINE std::size_t align_on(std::size_t value, std::size_t align)
  {
    BOOST_ASSERT_MSG( ::boost::simd::is_power_of_2(align)
                    , "Invalid alignment boundary. You tried to align an "
                      "address or a value on a non-power of 2 boundary."
                    );

    return (value+align-1) & ~(align-1);
  }

  /// @overload
  template<class T> BOOST_FORCEINLINE
  T* align_on(T* value, std::size_t align)
  {
    std::size_t v = reinterpret_cast<std::size_t>(value);
    return reinterpret_cast<T*>(::boost::simd::align_on(v,align));
  }

  /*!
    @brief Align value or pointer on current SIMD alignment boundary and
           return the next aligned value or pointer.

    Force the alignment of an  integral value or pointer @c value
    on the current SIMD alignment boundary.

    @par Semantic:

    For any integral value or pointer @c v

    @code
    auto r = align_on(v,a);
    @endcode

    is equivalent to:

    @code
    auto r = align_on(v,BOOST_SIMD_CONFIG_ALIGNMENT);
    @endcode

    When called on a pointer, the returned pointer is correctly flagged as aligned
    usign compiler-specific attributes.

    @see align_ptr
    @see meta::align_ptr

    @usage{memory/align_on_default.cpp}

    @param value Value or pointer to align

    @return The aligned integral value or pointer
  **/
  BOOST_FORCEINLINE std::size_t align_on(std::size_t value)
  {
    return ::boost::simd::align_on(value,BOOST_SIMD_CONFIG_ALIGNMENT);
  }

  /// @overload
  template<class T> BOOST_FORCEINLINE
  typename ::boost::simd::meta::align_ptr<T>::type align_on(T* value)
  {
    return ::boost::simd::align_ptr ( ::boost::simd::
                                          align_on( value
                                                  , BOOST_SIMD_CONFIG_ALIGNMENT
                                                  )
                                    );
  }
} }

#endif
