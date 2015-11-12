//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_DOWNGRADE_HPP_INCLUDED
#define BOOST_DISPATCH_META_DOWNGRADE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the boost::dispatch::meta::downgrade \metafunction
 */

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
  //============================================================================
  /*!
   * Returns the input type rebound with a type that is twice as small as
   * its primitive, with optional sign change.\
   *
   * \tparam Type Hierarchizable type to downgrade.
   * \tparam Sign Optional sign to use while downgrading \c Type. If unspecified,
   * \c Sign is equals to the sign of \c Type.
   *
   * \par Models:
   *
   * \metafunction
   *
   * \par Semantic:
   *
   * \code
   * typedef boost::dispatch::meta::downgrade<T, Sign>::type r;
   * \endcode
   *
   * is equivalent to:
   *
   * \code
   * typedef make_floating< max< sizeof(primitive_of<T>::type)/2
   *                       , sizeof(float)
   *                       >::value
   *                  , factory_of<T>::type
   *                  >::type                                  r;
   * \endcode
   *
   * if \c primitive_of<T> is of hierarchy boost::dispatch::meta::floating_
   * and to:
   *
   * \code
   * typedef make_integer< max<sizeof(primitive_of<T>::type)/2, 1>::value
   *                     , Sign
   *                     , factory_of<T>::type
   *                     >::type                                r;
   * \endcode
   *
   * otherwise.
   *
   * \par Usage:
   *
   * \include downgrade.cpp
   */
  //============================================================================
  template<class T, class Sign = void>
  struct downgrade;
} } }

namespace boost { namespace dispatch { namespace details
{
  template<class T, class Sign, class Lambda, class Enable = void>
  struct downgrade_impl;

  template<class T, class Sign, class Lambda>
  struct downgrade_impl< T, Sign, Lambda
                       , typename enable_if< boost::is_integral<T> >::type
                       >
  {
    BOOST_STATIC_CONSTANT ( std::size_t
                          , size = (sizeof(T) > 1) ? sizeof(T)/2 : 1
                          );

    typedef typename mpl::eval_if < is_void<Sign>
                                  , meta::sign_of<T>
                                  , mpl::identity<Sign>
                                  >::type         sign;

    typedef typename meta::make_integer<size,sign,Lambda>::type type;
  };

  template<class T, class Sign, class Lambda>
  struct downgrade_impl< T, Sign, Lambda
                       , typename enable_if< boost::is_floating_point<T> >::type
                       >
  {
    BOOST_STATIC_CONSTANT ( std::size_t
                          , size = (sizeof(T) > 1) ? sizeof(T)/2 : 1
                          );

    typedef typename meta::make_floating<size,Lambda>::type type;
  };

  template<class Sign>
  struct downgrade_fusion
  {
    template<class Sig>
    struct result;

    template<class This, class X>
    struct result<This(X)>
         : meta::downgrade<typename meta::strip<X>::type, Sign>
    {
    };

    template<class X>
    typename meta::downgrade<X>::type operator()(X const&) const;
  };

  template<class T, class Sign, class Lambda>
  struct downgrade_impl< T, Sign, Lambda
                       , typename enable_if< boost::fusion::traits::is_sequence<T> >::type
                       >
       : Lambda::template apply< typename boost::fusion::result_of::
                                 as_vector< typename boost::fusion::result_of::
                                            transform<T, downgrade_fusion<Sign> >::type
                                          >::type
                               >
  {
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  template<class T,class Sign>
  struct downgrade
  {
    typedef typename meta::factory_of<T>::type  lambda;
    typedef typename meta::primitive_of<T>::type  base;
    typedef typename meta::strip<base>::type  stripped;
    typedef typename details::downgrade_impl<stripped, Sign, lambda>::type type;
  };

  template<class T, class Sign>
  struct downgrade<T&,Sign>       : downgrade<T,Sign> {};

  template<class T, class Sign>
  struct downgrade<T const,Sign>  : downgrade<T,Sign> {};
} } }

#endif
