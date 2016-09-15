//==================================================================================================
/*!
  @file

  Defines functions properties hierarchies

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_FUNCTIONS_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_FUNCTIONS_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief Root function hierarchy tag

    The function_ hierarchy classify function related informations.
  **/
  template<typename T> struct function_ : unspecified_<T>
  {
    using parent        =  unspecified_<T>;
  };

  /*!
    @ingroup group-tag
    @brief Abstract function hierarchy tag

    Function object classified as abstract_ if they represent higher-order functions

    @tparam F Function object type
  **/
  template<typename F> struct abstract_ : function_<F>
  {
    using parent = function_<F>;
  };

  /*!
    @ingroup group-tag
    @brief Elementwise function hierarchy tag

    Function object classified as elementwise_ if they can be used as argument to the map
    higher-order function.

    @tparam F Function object type
  **/
  template<typename F> struct elementwise_ : function_<F>
  {
    using parent = function_<F>;
  };

  /*!
    @ingroup group-tag
    @brief Constant value function hierarchy tag

    Function object classified as constant_value if they evaluate to a value independant of their
    input values.

    @tparam F Function object type
  **/
  template<typename F> struct constant_value_ : elementwise_<F>
  {
    using parent = elementwise_<F>;
  };

  /*!
    @ingroup group-tag
    @brief Reductive function hierarchy tag

    Function object classified as reduction_ if they can be used as argument to the fold
    higher-order function.

    @tparam F Function object type
    @tparam BinOp Function object type for the underlying binary function used by fold
    @tparam NeutralElement Function object type returning the neutral element value of BinOp
  **/
  template<typename F, typename BinOp, typename NeutralElement>
  struct reduction_ : function_<F>
  {
    using parent = function_<F>;
  };

  /*!
    @ingroup group-tag
    @brief Cumulative function hierarchy tag

    Function object classified as cumulative_ if they can be used as argument to the scan
    higher-order function.

    @tparam F Function object type
    @tparam BinOp Function object type for the underlying binary function used by scan
    @tparam NeutralElement Function object type returning the neutral element value of BinOp
  **/
  template<typename F, typename BinOp, typename NeutralElement>
  struct cumulative_ : function_<F>
  {
    using parent = function_<F>;
  };

  /*!
    @ingroup group-tag
    @brief Multi-return function hierarchy tag

    Function object classified as tieable_ if they may return multiple values as a tie expression.

    @tparam F Function object type
  **/
  template<typename F> struct tieable_ : function_<F>
  {
    using parent = function_<F>;
  };
} }

#endif
