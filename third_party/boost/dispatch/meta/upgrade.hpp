//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_UPGRADE_HPP_INCLUDED
#define BOOST_DISPATCH_META_UPGRADE_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// Returns the input type rebound with a type that is twice as big
// as its primitive, with optional sign.
// If the primitive type is floating-point, sign is ignored.
// See: http://nt2.metascale.org/sdk/meta/traits/upgrade.html
//////////////////////////////////////////////////////////////////////////////

#include <boost/dispatch/meta/sign_of.hpp>
#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/dispatch/meta/make_integer.hpp>
#include <boost/dispatch/meta/make_floating.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T,class Sign = void>
  struct upgrade;
} } }

namespace boost { namespace dispatch { namespace details
{
  template<class T, class Sign, class Lambda, class Enable = void>
  struct upgrade_impl;

  template<class T, class Sign, class Lambda>
  struct upgrade_impl< T, Sign, Lambda
                     , typename enable_if< boost::is_integral<T> >::type
                     >
  {
    BOOST_STATIC_CONSTANT ( std::size_t
                          , size = (sizeof(T) < 8) ? sizeof(T)*2 : 8
                          );

    typedef typename mpl::eval_if < is_void<Sign>
                                  , meta::sign_of<T>
                                  , mpl::identity<Sign>
                                  >::type         sign;

    typedef typename
            meta::make_integer<size,sign,Lambda>::type type;
  };

  template<class T, class Sign, class Lambda>
  struct upgrade_impl< T, Sign, Lambda
                     , typename enable_if< boost::is_floating_point<T> >::type
                     >
  {
    BOOST_STATIC_CONSTANT ( std::size_t
                          , size = (sizeof(T) < 8) ? sizeof(T)*2 : 8
                          );

    typedef typename meta::make_floating<size,Lambda>::type  type;
  };

  template<class Sign>
  struct upgrade_fusion
  {
    template<class Sig>
    struct result;

    template<class This, class X>
    struct result<This(X)>
         : meta::upgrade<typename meta::strip<X>::type, Sign>
    {
    };

    template<class X>
    typename meta::upgrade<X>::type operator()(X const&) const;
  };

  template<class T, class Sign, class Lambda>
  struct upgrade_impl< T, Sign, Lambda
                     , typename enable_if< boost::fusion::traits::is_sequence<T> >::type
                     >
       : Lambda::template apply< typename boost::fusion::result_of::
                                 as_vector< typename boost::fusion::result_of::
                                            transform<T, upgrade_fusion<Sign> >::type
                                          >::type
                               >
  {
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For any type, return the integer type of size equals to sizeof(T)*2
  // with an optional sign change
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Sign>
  struct upgrade
  {
    typedef typename meta::factory_of<T>::type  lambda;
    typedef typename meta::primitive_of<T>::type  base;
    typedef typename meta::strip<base>::type  stripped;
    typedef typename details::upgrade_impl<stripped, Sign, lambda>::type type;
  };

  template<class T, class Sign>
  struct upgrade<T&,Sign> : upgrade<T,Sign> {};

  template<class T, class Sign>
  struct upgrade<T const,Sign> : upgrade<T,Sign> {};
} } }

#endif
