//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_DETAILS_PROPERTY_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_DETAILS_PROPERTY_OF_HPP_INCLUDED

#include <boost/dispatch/meta/details/properties.hpp>
#include <boost/dispatch/meta/details/hierarchy_base.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/utility/enable_if.hpp>
#include <climits>

namespace boost { namespace dispatch { namespace details
{
  //============================================================================
  // implementation details for property_of on integers
  //============================================================================
  template<class T,class Origin,std::size_t Size, bool Signed>
  struct property_of_ints;

  template<class T,class Origin>
  struct  property_of < T
                      , Origin
                      , typename boost::
                        enable_if_c < boost::is_integral<T>::value>::type
                      >
          : details::property_of_ints < T
                                      , Origin
                                      , sizeof(T)*CHAR_BIT
                                      , boost::
                                        is_signed<T>::value
                                      >
  {};

}

namespace meta
{
  //============================================================================
  // Overload for non integral native types
  //============================================================================
  template<class Origin>
  struct property_of<void, Origin>
  {
    typedef meta::void_<Origin> type;
  };

  template<class Origin>
  struct property_of<float, Origin>
  {
    typedef meta::single_<Origin>  type;
  };

  template<class Origin>
  struct property_of<double, Origin>
  {
    typedef meta::double_<Origin> type;
  };

  template<class Origin>
  struct property_of<long double, Origin>
  {
    typedef meta::floating_<Origin> type;
  };
}

namespace details
{
  //============================================================================
  // implementation details for property_of - overload for bool
  //============================================================================
  template<class Origin>
  struct property_of_ints<bool,Origin,sizeof(bool)*CHAR_BIT,false>
  {
    typedef meta::bool_<Origin>  type;
  };

  //============================================================================
  // implementation details for property_of - overload for integral sized type
  //============================================================================
  template<class T,class Origin> struct property_of_ints<T,Origin,8,true>
  {
    typedef meta::int8_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,16,true>
  {
    typedef meta::int16_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,32,true>
  {
    typedef meta::int32_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,64,true>
  {
    typedef meta::int64_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,8,false>
  {
    typedef meta::uint8_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,16,false>
  {
    typedef meta::uint16_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,32,false>
  {
    typedef meta::uint32_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,64,false>
  {
    typedef meta::uint64_<Origin> type;
  };
} } }

#endif
