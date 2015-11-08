//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_FUSION_HPP_INCLUDED
#define BOOST_DISPATCH_META_FUSION_HPP_INCLUDED

/*!
 * \file
 * \brief Register Fusion sequence and std::array as Hierarchizable
 */

#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/property_of.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/proto/traits.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/array.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //==========================================================================
  /*! Fusion sequence hierarchy type                                        */
  //==========================================================================
  template<class T> struct fusion_sequence_ : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };

  //==========================================================================
  /*! boost::array hierarchy type                                           */
  //==========================================================================
  template<typename T, typename N>
  struct array_ : array_<typename T::parent, N>
  {
    typedef array_<typename T::parent, N> parent;
  };

  template<class T, typename N>
  struct array_<unspecified_<T>, N> : fusion_sequence_<T>
  {
    typedef fusion_sequence_<T> parent;
  };

  //============================================================================
  // Requirements for Buildable
  //============================================================================
  template<class T, std::size_t N>
  struct value_of< boost::array<T,N> >
  {
    typedef T type;
  };

  template<class T, std::size_t N>
  struct model_of< boost::array<T, N> >
  {
    struct type
    {
      template<class X>
      struct apply
      {
        typedef boost::array<X, N> type;
      };
    };
  };
}

namespace details
{
  template<class T>
  struct is_array : boost::mpl::false_ {};

  template<class T, std::size_t N>
  struct is_array< boost::array<T, N> > : boost::mpl::true_ {};

  template<class T,class Origin>
  struct  hierarchy_of< T
                      , Origin
                      , typename boost
                        ::enable_if_c < boost::fusion
                                        ::traits::is_sequence<T>::value
                                        && !is_array<T>::value
                                        && !proto::is_expr<T>::value
                                      >::type
                      >
  {
    typedef meta::fusion_sequence_<Origin> type;
  };

  template<class T,class Origin>
  struct   property_of< T
                      , Origin
                      , typename boost
                        ::enable_if_c < boost::fusion
                                        ::traits::is_sequence<T>::value
                                        && !is_array<T>::value
                                        && !proto::is_expr<T>::value
                                      >::type
                      >
  {
    typedef meta::fusion_sequence_<Origin> type;
  };
}

namespace meta
{
  template<class T, std::size_t N,class Origin>
  struct  hierarchy_of< boost::array<T,N>
                      , Origin
                      >
  {
    typedef array_< typename hierarchy_of<T, Origin>::type
                  , boost::mpl::size_t<N>
                  > type;
  };

} } }

#endif
