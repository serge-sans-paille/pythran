//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_MEMORY_FUNCTIONS_CONTAINER_VALUE_HPP_INCLUDED
#define NT2_MEMORY_FUNCTIONS_CONTAINER_VALUE_HPP_INCLUDED

#include <nt2/memory/functions/value.hpp>
#include <boost/proto/traits.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::value_, tag::cpu_
                            , (A0)(D)(N)(Tag)
                            , ((node_<A0,unspecified_<Tag>,N,D>))
                            )
  {
    typedef typename boost::proto::result_of::value<A0&>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      return boost::proto::value(a0);
    }
  };
} }

#endif
