//==================================================================================================
/*!
  @file

  Defines the signed and unsigned type hierarchies

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_SIGNED_TYPES_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_SIGNED_TYPES_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/integer.hpp>
#include <boost/simd/detail/dispatch/meta/behave_as.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief Signed types hierarchy tag

    Types are classified as signed_type_ if they have the proper sign.

    @tparam T     Base hierarchy
    @tparam Sign  Sign encoded as @c signed or @c unsigned
  **/
  template<typename T, typename Sign> struct signed_type_ {};

  /// @internal
  template<typename T>
  struct signed_type_<T,signed> : std::conditional< behave_as<T,std::is_integral<nsm::_1>>::value
                                                  , integer_<T>
                                                  , arithmetic_<T>
                                                  >::type
  {
    using parent = typename std::conditional< behave_as<T,std::is_integral<nsm::_1>>::value
                                            , integer_<T>
                                            , arithmetic_<T>
                                            >::type;
  };

  /// @internal
  template<typename T> struct signed_type_<T,unsigned> : integer_<T>
  {
    using parent = integer_<T>;
  };

  /*!
    @ingroup group-tag
    @brief signed type hierarchy tag

    Types are classified as signed_ if they behaves as one of the signed types.

    @tparam T Base hierarchy
  **/
  template<typename T> using signed_ = signed_type_<T,signed>;

  /*!
    @ingroup group-tag
    @brief unsigned type hierarchy tag

    Types are classified as unsigned_ if they behaves as one of the unsigned types.

    @tparam T Base hierarchy
  **/
  template<typename T> using unsigned_ = signed_type_<T,unsigned>;

  /*!
    @ingroup group-tag
    @brief Signed types hierarchy tag

    Types are classified as signed_type_ if they have the proper sign.

    @tparam T     Base hierarchy
    @tparam Sign  Sign encoded as @c signed or @c unsigned
  **/
  template<typename T, typename Sign>
  struct signed_integral_ : signed_type_<T,Sign>
  {
    using parent = signed_type_<T,Sign>;
  };

  /*!
    @ingroup group-tag
    @brief unsigned integral type hierarchy tag

    Types are classified as int_ if they behaves as one of the unsigned integral types.

    @tparam T Base hierarchy
  **/
  template<typename T> using uint_  = signed_integral_<T,unsigned>;

  /*!
    @ingroup group-tag
    @brief signed integral type hierarchy tag

    Types are classified as int_ if they behaves as one of the signed integral types.

    @tparam T Base hierarchy
  **/
  template<typename T> using int_   = signed_integral_<T,signed>;
} }

#endif
