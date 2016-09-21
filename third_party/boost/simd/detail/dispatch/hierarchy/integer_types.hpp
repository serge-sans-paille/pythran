//==================================================================================================
/*!
  @file

  Defines the type hierarchies for IEEE-754 like types

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_INTEGER_TYPES_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_INTEGER_TYPES_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/sized_types.hpp>
#include <cstddef>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief Sized integral hierarchy tag

    Types are classified as ints_ if they are integral types of sizeof Size.

    @tparam T     Base hierarchy
    @tparam Size  Size in bits
  **/
  template<typename T,std::size_t Size> struct ints_  : sized_type_<T,Size>
  {
    using parent = sized_type_<T,Size>;
  };

  /*!
    @ingroup group-tag
    @brief 8 bits integers hierarchy tag

    Types are classified as ints8_ if they are any kind - signed or not - of 8 bits integrals.

    @tparam T Base hierarchy
  **/
  template<typename T> using ints8_   = ints_<T,8>;

  /*!
    @ingroup group-tag
    @brief 16 bits integers hierarchy tag

    Types are classified as ints16_ if they are any kind - signed or not - of 16 bits integrals.

    @tparam T Base hierarchy
  **/
  template<typename T> using ints16_  = ints_<T,16>;

    /*!
    @ingroup group-tag
    @brief 32 bits integers hierarchy tag

    Types are classified as ints32_ if they are any kind - signed or not - of 32 bits integrals.

    @tparam T Base hierarchy
  **/
  template<typename T> using ints32_  = ints_<T,32>;

    /*!
    @ingroup group-tag
    @brief 64 bits integers hierarchy tag

    Types are classified as ints64_ if they are any kind - signed or not - of 64 bits integrals.

    @tparam T Base hierarchy
  **/
  template<typename T> using ints64_  = ints_<T,64>;

  /*!
    @ingroup group-tag
    @brief Integer hierarchy tag

    Types are classified as integral_ if they have the proper sizeof and sign.

    @tparam T     Base hierarchy
    @tparam N     Size in bits
    @tparam Sign  Sign encoded as @c signed or @c unsigned
  **/
  template<typename T, std::size_t N, typename Sign>
  struct integral_ : ints_<T,N>
  {
    using parent = ints_<T,N>;
  };

  /*!
    @ingroup group-tag
    @brief 8 bits signed integer hierarchy tag

    Types are classified as int8_ if they are signed 8 bits integral types.

    @tparam T Base hierarchy
  **/
  template<typename T> using int8_ = integral_<T,8,signed>;

  /*!
    @ingroup group-tag
    @brief 16 bits signed integer hierarchy tag

    Types are classified as int16_ if they are signed 16 bits integral types.

    @tparam T Base hierarchy
  **/
  template<typename T> using int16_ = integral_<T,16,signed>;

  /*!
    @ingroup group-tag
    @brief 32 bits signed integer hierarchy tag

    Types are classified as int32_ if they are signed 32 bits integral types.

    @tparam T Base hierarchy
  **/
  template<typename T> using int32_ = integral_<T,32,signed>;

  /*!
    @ingroup group-tag
    @brief 64 bits signed integer hierarchy tag

    Types are classified as int64_ if they are signed 64 bits integral types.

    @tparam T Base hierarchy
  **/
  template<typename T> using int64_ = integral_<T,64,signed>;

  /*!
    @ingroup group-tag
    @brief 8 bits signed integer hierarchy tag

    Types are classified as int8_ if they are unsigned 8 bits integral types.

    @tparam T Base hierarchy
  **/
  template<typename T> using uint8_ = integral_<T,8,unsigned>;

  /*!
    @ingroup group-tag
    @brief 16 bits signed integer hierarchy tag

    Types are classified as int16_ if they are unsigned 16 bits integral types.

    @tparam T Base hierarchy
  **/
  template<typename T> using uint16_ = integral_<T,16,unsigned>;

  /*!
    @ingroup group-tag
    @brief 32 bits signed integer hierarchy tag

    Types are classified as int32_ if they are unsigned 32 bits integral types.

    @tparam T Base hierarchy
  **/
  template<typename T> using uint32_ = integral_<T,32,unsigned>;

  /*!
    @ingroup group-tag
    @brief 64 bits signed integer hierarchy tag

    Types are classified as int64_ if they are unsigned 64 bits integral types.

    @tparam T Base hierarchy
  **/
  template<typename T> using uint64_ = integral_<T,64,unsigned>;
} }

#endif
