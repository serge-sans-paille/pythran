//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_WHEREIJ_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_WHEREIJ_HPP_INCLUDED

#include <nt2/core/functions/whereij.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_ < A0, nt2::tag::whereij_
                                      , N, nt2::container::domain
                                      >
                              ))
                              (generic_< integer_<State> >)
                              (target_<unspecified_<Data> >)
                            )
  {
    typedef typename Data::type                                   result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, State const& p, Data const& t) const
    {
      typedef typename meta::as_index<result_type>::type                i_t;
      typedef typename result_of::as_subscript<_2D,i_t>::type           s_t;

      s_t pos  = as_subscript(_2D(a0.extent()),enumerate<i_t>(p));

      return if_else( boost::proto::value(boost::proto::child_c<0>(a0))(pos[0],pos[1])
                    , run(boost::proto::child_c<1>(a0), p, t)
                    , run(boost::proto::child_c<2>(a0), p, t)
                    );
    }
  };
} }

#endif
