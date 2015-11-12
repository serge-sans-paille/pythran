//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_AS_FLOATING_HPP_INCLUDED
#define BOOST_DISPATCH_META_AS_FLOATING_HPP_INCLUDED

/*!
 * @file
 * @brief Define the boost::dispatch::meta::as_floating @metafunction.
 **/

#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/make_floating.hpp>
#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/dispatch/meta/is_fundamental.hpp>

/// TODO: Try to find an implementation with less template instanciation
namespace boost { namespace dispatch { namespace meta
{
  /*!
   * @brief Compute a floating point type common to a type set.
   *
   * Computes the smallest floating point type able to hold a value of the
   * common type of its input parameters.
   *
   * @tparam Args Primitive types to transform
   *
   * @par Models:
   *
   * @metafunction
   *
   * @par Semantic:
   *
   * For any types @c Args,
   *
   * @code
   * typedef as_floating<Args>::type type;
   * @endcode
   *
   * is equivalent to:
   *
   * @code
   *  typedef make_floating < sizeof(primitive_of<Ai>::type)
   *                        , factory_of<Ai>::type
   *                        >::type                           type;
   * @endcode
   *
   * where @c Ai is the type with the largest @c sizeof among @c Args...
   * If any of the @c Ai is not a Primitive type, a
   * @c BOOST_DISPATCH_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_AS_FLOATING static
   * assertion is triggered.
   *
   * @par Usage:
   *
   * @include as_floating.cpp
   **/
#if defined(DOXYGEN_ONLY)
  template<typename... Args> struct  as_floating {};
#else
  template<class A0, class A1 = void, class A2 = void, class A3 = void>
  struct as_floating;

  template<class T>
  struct  as_floating<T>
        : meta::
          make_floating
          < sizeof( typename meta::
                    primitive_of<typename meta::strip<T>::type>::type
                  )
          , typename meta::
            factory_of<typename meta::strip<T>::type>::type
          >
  {
    //**************************** STATIC ASSERT *****************************//
    //     A type with a non-fundamental primitive is used in a call to the   //
    //            boost::dispatch::meta::as_floating meta-function.           //
    //**************************** STATIC ASSERT *****************************//
    BOOST_MPL_ASSERT_MSG
    ( (is_fundamental < typename
                        meta::primitive_of<typename meta::strip<T>::type>::type
                      >::value
      )
    , BOOST_DISPATCH_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_AS_FLOATING
    , (T&)
    );
  };

  template<class A0, class A1>
  struct  as_floating<A0, A1>
        : as_floating
          < typename mpl::
            if_c< ( sizeof( typename meta::
                            primitive_of<typename meta::strip<A0>::type>::type
                          )
                  < sizeof( typename meta::
                            primitive_of<typename meta::strip<A1>::type>::type
                          )
                  )
                , A1
                , A0
                >::type
          >
  {};

  template<class A0, class A1, class A2>
  struct  as_floating<A0, A1, A2>
        : as_floating
          < typename mpl::
            if_c< ( sizeof( typename meta::
                            primitive_of<typename meta::strip<A0>::type>::type
                          )
                  < sizeof( typename meta::
                            primitive_of<typename meta::strip<A1>::type>::type
                          )
                  )
                , A1
                , A0
                >::type
          , A2
          >
  {};

  template<class A0, class A1, class A2, class A3>
  struct  as_floating
        : as_floating
          < typename mpl::
            if_c< ( sizeof( typename meta::
                            primitive_of<typename meta::strip<A0>::type>::type
                          )
                  < sizeof( typename meta::
                            primitive_of<typename meta::strip<A1>::type>::type
                          )
                  )
                , A1
                , A0
                >::type
            , A2
            , A3
          >
  {};
#endif
} } }

#endif
