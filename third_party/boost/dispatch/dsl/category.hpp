//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_DSL_CATEGORY_HPP_INCLUDED
#define BOOST_DISPATCH_DSL_CATEGORY_HPP_INCLUDED

/*!
 * @file
 * @brief Defines Boost.Proto expression elements hierarchies
 **/

#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>

namespace boost { namespace dispatch { namespace details
{
  template<class T, class Enable = void>
  struct expr_of
       : expr_of<typename meta::value_of<T>::type>
  {
  };

  template<class T>
  struct expr_of<T, typename T::proto_is_expr_>
  {
    typedef T type;
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  /*!
   * @brief Boost.Proto top-level expression hierachy
   *
   * ast_ is the hierarchy representing any Boost.Proto expression of any kind.
   *
   * @par Models:
   * Hierarchy
   *
   * @tparam T Hierarchized type
   **/
  template<class T, class D>
  struct ast_ : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };

  /*!
   * @brief Boost.Proto expression node hierachy
   *
   * node_ is the hierarchy representing a Boost.Proto expression node of tag
   * @c Tag, semantic hierarchy @c T  and with @c N children. Parent hierarchies
   * of node_ are computed by walking the parent hierarchy of @c Tag. Once
   * hitting the unspecified_ hierarchy, node_ parent is computed as a ast_
   * hierarchy.
   *
   * @par Models:
   * Hierarchy
   *
   * @tparam T    Expression semantic hierarchy
   * @tparam Tag  Expresson node tag hierarchy
   * @tparam N    Expression arity
   **/
  template<class T, class Tag, class N, class D>
  struct node_ : node_<T, typename Tag::parent, N, D>
  {
    typedef node_<T, typename Tag::parent, N, D> parent;
  };

  /// INTERNAL ONLY
  template<class T, class Tag, class N, class D>
  struct node_<T, unspecified_<Tag>, N, D> : ast_<T, D>
  {
    typedef ast_<T, D> parent;
  };

  /*!
   * @brief Boost.Proto expression hierachy
   *
   * expr_ is the hierarchy representing a Boost.Proto expression of tag @c Tag,
   * semantic hierarchy @c T and with @c N children. Parent hierarchies of expr_
   * are computed by walking the parent hierarchy of @c T. Once hitting the
   * unspecified_ hierarchy, expr_ parent is computed as a node_ hierarchy.
   *
   * @par Models:
   * Hierarchy
   *
   * @tparam T    Expression semantic hierarchy
   * @tparam Tag  Expresson node tag hierarchy
   * @tparam N    Expression arity
   **/
  template<class T, class Tag, class N>
  struct expr_ : expr_<typename T::parent, Tag, N>
  {
    typedef expr_<typename T::parent, Tag, N>  parent;
  };

  /// INTERNAL ONLY
  template<class T, class Tag, class N>
  struct expr_< unspecified_<T>, Tag, N> : node_<T, Tag, N, typename details::expr_of<T>::type::proto_domain>
  {
    typedef node_<T, Tag, N, typename details::expr_of<T>::type::proto_domain> parent;
  };
} } }

namespace boost { namespace dispatch { namespace details
{
  /// INTERNAL ONLY
  /// Proto expression hierarchy computation
  template<class T, class Origin>
  struct hierarchy_of< T
                     , Origin
                     , typename T::proto_is_expr_
                     >
  {
    typedef typename meta::semantic_of<T>::type  semantic_type;

    typedef meta::expr_ < typename meta::hierarchy_of<semantic_type, Origin>::type
                        , typename meta::hierarchy_of<typename T::proto_tag>::type
                        , typename T::proto_arity
                        >                                          type;
  };

  template<class T>
  struct value_of< T
                 , typename T::proto_is_expr_
                 >
    : meta::semantic_of<T>
  {
  };

  template<class T>
  struct value_of_cv< T const
                    , typename T::proto_is_expr_
                    >
    : meta::semantic_of<T const>
  {
  };

  template<class T>
  struct value_of_cv< T&
                    , typename T::proto_is_expr_
                    >
    : meta::semantic_of<T&>
  {
  };
} } }

#endif
