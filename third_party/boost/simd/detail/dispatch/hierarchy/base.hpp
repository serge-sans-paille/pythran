//==================================================================================================
/*!
  @file

  Defines the basic hierarchies

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_BASE_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_BASE_HPP_INCLUDED

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief Root hierarchy tag

    The unknown_ hierarchy classify everything and is used as a top hierarchy
  **/
  template<typename T> struct unknown_
  {
    using parent        =  unknown_;
    using hierarchy_tag =  void;
  };

  /*!
    @ingroup group-tag
    @brief Root type hierarchy tag

    The type_ hierarchy classify type related informations.
  **/
  template<typename T> struct type_ : unknown_<T>
  {
    using parent        =  unknown_<T>;
  };
} }

#endif
