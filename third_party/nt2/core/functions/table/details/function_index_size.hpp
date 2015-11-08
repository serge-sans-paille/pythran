//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_DETAILS_FUNCTION_INDEX_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_DETAILS_FUNCTION_INDEX_SIZE_HPP_INCLUDED

#include <nt2/core/functions/function_index.hpp>
#include <nt2/core/functions/table/details/make_size.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Size of a function_index call node is depends of the indexers
  //============================================================================
  template<class Expr, class Domain, int N>
  struct size_of<tag::function_index_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::
            child_c<Expr&, 0>::value_type           indices;

    typedef typename boost::proto::result_of::
            value< typename boost::proto::result_of::
                   child_c<Expr&, 1>::value_type
                 >::type                            shape;
    typedef typename boost::proto::result_of::
            value< typename boost::proto::result_of::
                   child_c<Expr&, 2>::value_type
                 >::type                            sizes;
    typedef typename boost::proto::result_of::
            value< typename boost::proto::result_of::
                   child_c<Expr&, 3>::value_type
                 >::type::type                      bases;

    typedef details::make_size< indices::proto_arity_c
                              , Domain
                              , shape
                              , sizes
                              , bases
                              , indices
                              >                                   impl;
    typedef typename impl::result_type                            result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return impl() ( boost::proto::value(boost::proto::child_c<1>(e))
                    , boost::proto::value(boost::proto::child_c<2>(e))
                    , bases()
                    , boost::proto::child_c<0>(e)
                    );
    }
  };
} }

#endif
