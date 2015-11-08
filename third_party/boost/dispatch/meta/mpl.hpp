//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_MPL_HPP_INCLUDED
#define BOOST_DISPATCH_META_MPL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Various memory hierarchy stuff
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/integral_c_tag.hpp>
#include <boost/mpl/if.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>

////////////////////////////////////////////////////////////////////////////////
// Specialize hierarchy for mpl integral types
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  template<class T> struct mpl_integral_ : mpl_integral_< typename T::parent >
  {
    typedef mpl_integral_< typename T::parent > parent;
  };

  template<class T>
  struct  mpl_integral_< unspecified_<T> >
        : hierarchy_of<typename T::value_type,T>::type
  {
    typedef typename hierarchy_of<typename T::value_type,T>::type parent;
  };
}

namespace details
{
  ////////////////////////////////////////////////////////////////////////////////
  // Some MPL introspection helpers
  ////////////////////////////////////////////////////////////////////////////////
  template<class T, class Enable = void>
  struct  has_mpl_tag
        : boost::mpl::false_ {};

  template<class T>
  struct  has_mpl_tag < T
                      , typename meta
                        ::enable_if_type< typename T::tag >::type
                      >
        : boost::mpl::true_ {};

  template<class T, bool EnableIf = has_mpl_tag<T>::value>
  struct  is_mpl_integral : boost::mpl::false_
  {};

  template<class T>
  struct  is_mpl_integral<T,true>
        : boost::is_same<typename T::tag,boost::mpl::integral_c_tag>
  {};

  template<class T,class Origin>
  struct  hierarchy_of< T
                      , Origin
                      , typename boost
                        ::enable_if_c<details::is_mpl_integral<T>::value>::type
                      >
  {
    typedef typename remove_const<Origin>::type stripped;
    typedef typename mpl::if_< is_same< T, stripped >, stripped, Origin>::type origin_;

    typedef meta::
    mpl_integral_< typename meta::
                   hierarchy_of< typename T::value_type
                               , origin_
                               >::type
                 >                                                            type;
  };

  template<class T>
  struct  value_of< T
                  , typename boost
                        ::enable_if_c<details::is_mpl_integral<T>::value>::type
                  >
  {
    typedef typename T::value_type type;
  };

} } }

#endif
