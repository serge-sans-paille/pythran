//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_DETAILS_AS_SIGNED_HPP_INCLUDED
#define BOOST_DISPATCH_META_DETAILS_AS_SIGNED_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/meta/is_fundamental.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/make_signed.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T> struct as_signed;
} } }

namespace boost { namespace dispatch { namespace details
{
  template<class T, class Enable = void>
  struct  as_signed_impl
        : boost::mpl::apply < typename meta::factory_of<T>::type
                            , typename meta::
                              as_signed< typename meta::primitive_of<T>::type
                                       >::type
                            >
  {};

  template<class T>
  struct  as_signed_impl< T
                        , typename boost::enable_if < typename meta::
                                                      is_fundamental<T>::type
                                                    >::type
                        >
        : boost::mpl::eval_if < boost::mpl::
                                bool_ <   boost::is_integral<T>::value
                                      &&  !boost::is_same<bool,T>::value
                                      >
                              , boost::make_signed<T>
                              , boost::mpl::identity<T>
                              > {};
} } }

#endif
