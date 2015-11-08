//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_SIZE_AS_HPP_INCLUDED
#define NT2_SDK_META_SIZE_AS_HPP_INCLUDED

/*!
  @file
  @brief Defines the size_as @metafunction
 **/

#include <boost/proto/traits.hpp>

namespace nt2 { namespace meta
{
  /*!
    @brief size_of helper for child-like value_type cases

    This pfo extracts the size type of the @c Nth child of an
    nt2 expression @c Expr to use as @c Expr size_of specialization.

    @tparam Expr nt2 expression to extract the size type from.
    @tparam N    Integral index of the chidl providing the size type.

    @par Compile-time Semantic:

    For any given nt2 expression @c Expr and any integral @c N,

    @code
    typedef meta::size_as<Expr,N>::result_type r;
    @endcode

    is equivalent to:

    @code
    typedef boost::proto::result_of::child_c<Expr&,N>::value_type::extent_type r;
    @endcode

    This behavior is tied to the fact nt2 expression stores their children by
    values.

    @par Runtime Semantic:

    For any given nt2 expression @c e of type @c Expr and any integral @c N,

    @code
    r = meta::size_as<Expr,N>()(e);
    @endcode

    is equivalent to:

    @code
    r = boost::proto::child_c<N>(e).extent();
    @endcode
   **/
  template<class Expr, int N> struct size_as
  {
    typedef typename  boost::proto::result_of
                    ::child_c<Expr&,N>::value_type::extent_type result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<N>(e).extent();
    }
  };
} }

#endif
