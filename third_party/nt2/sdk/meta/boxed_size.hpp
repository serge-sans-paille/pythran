//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_BOXED_SIZE_HPP_INCLUDED
#define NT2_SDK_META_BOXED_SIZE_HPP_INCLUDED

#include <boost/proto/traits.hpp>

namespace nt2 { namespace meta
{
  /*!
    @brief


  **/
  template<class Expr, int N> struct boxed_size
  {
    // The size is contained in the first child : box<Size>
    typedef typename boost::proto::result_of::child_c<Expr&,N>::type  c0_t;
    typedef typename boost::proto::result_of::value<c0_t>::value_type result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::value( boost::proto::child_c<N>(e) );
    }
  };
} }

#endif
