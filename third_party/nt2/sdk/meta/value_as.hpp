//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_VALUE_AS_HPP_INCLUDED
#define NT2_SDK_META_VALUE_AS_HPP_INCLUDED

/*!
  @file
  @brief Defines the value_as @metafunction
 **/

#include <boost/proto/traits.hpp>

namespace nt2 { namespace meta
{
  /*!
    @brief value_type helper for child-like value_type cases

    This @metafunction extracts the value type of the @c Nth child of an
    nt2 expression @c Expr to use as @c Expr value_type specialization.

    @note value_as doesn't perform any checks on the validity of the result
    with respect to a given expression hierarchy. Additionnal compile-time
    assertiosn may be included in the value_type specialisation itself.

    @tparam Expr nt2 expression to extract the value type from.
    @tparam N    Integral index of the chidl providing the value type.

    @par Semantic:

    For any given nt2 expression @c Expr and any integral @c N,

    @code
    typedef meta::value_as<Expr,N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef boost::proto::result_of::child_c<Expr&,N>::value_type::value_type r;
    @endcode

    This behavior is tied to the fact nt2 expression stores their children by
    values.
   **/
  template<class Expr, int N> struct value_as
  {
    typedef typename  boost::proto::result_of
                    ::child_c<Expr&,N>::value_type::value_type  type;
  };
} }

#endif
