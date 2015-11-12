//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_ALIGN_PTR_HPP_INCLUDED
#define BOOST_SIMD_META_ALIGN_PTR_HPP_INCLUDED

#include <boost/simd/preprocessor/parameters.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>
#include <boost/simd/preprocessor/aligned_type.hpp>
#include <boost/simd/preprocessor/assume_aligned.hpp>

namespace boost { namespace simd {  namespace meta
{
#if defined(DOXYGEN_ONLY)
  /*!
    @brief Apply alignment attribute to type

    Return the compiler specific, attribute ridden version of @c Type so it
    is recognized as being aligned on a boundary equal to @c Alignment.

    @par Semantic:

    For any type @c T and any integral value @c Alignment:

    @code
    typedef meta::align_ptr<T,Alignment>::type r;
    @endcode

    is equivalent to:

    @code
    typedef T* aligned_attribute r;
    @endcode

    where @a aligned_attribute is a compiler specific attribute indicating that
    said type will be used to store an address aligned on @c Alignment. On some
    compilers, the @a aligned_attribute is not available and the type returned
    by meta::align_ptr will be a simple pointer to @c T.

    @par Models:

    @metafunction

    @usage{meta/align_ptr.cpp}

    @tparam T     Type to mark as aligned.
    @tparam Align Integral power of two alignment boundary. By default,
            @c Align is equal to current SIMD extension alignment boundary.
  **/
  template<typename T, std::size_t Alignment = BOOST_SIMD_CONFIG_ALIGNMENT>
  struct align_ptr
  {
    typedef details::unspecified type;
  };
#else
  template<typename T, std::size_t Alignment = BOOST_SIMD_CONFIG_ALIGNMENT>
  struct align_ptr;
#endif

#define M0(z,n,t)                                                              \
template<typename T> struct align_ptr<T,n>                                     \
{                                                                              \
  typedef BOOST_SIMD_ALIGNED_TYPE_ON_TPL(T,n) base;                            \
  typedef base*                           type;                                \
                                                                               \
  static type value(T* pointer)                                                \
  {                                                                            \
    BOOST_SIMD_ASSUME_ALIGNED(type,pointer,n);                                 \
    return static_cast<type>(pointer);                                         \
  }                                                                            \
};                                                                             \
/**/

  BOOST_SIMD_PP_REPEAT_POWER_OF_2_BIG(M0, ~)

#undef M0

} } }

#endif
