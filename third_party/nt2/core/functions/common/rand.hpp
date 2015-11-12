//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_RAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_RAND_HPP_INCLUDED

#include <nt2/core/functions/rand.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/core/utility/randstream.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // rand evaluation
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1,nt2::tag::rand_
                                      , boost::mpl::long_<2>
                                      , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0& result_type;

    result_type operator()(A0& a0, A1& a1) const
    {
      // Setup lhs memory using size informations from rhs
      a0.resize( boost::proto::value(boost::proto::child_c<0>(a1)) );

      // Forward to current random_stream and fill the data
      current_prng_.generator_->rand(a0.raw(),0,nt2::numel(a0));

      return a0;
    }
  };
} }

#endif
