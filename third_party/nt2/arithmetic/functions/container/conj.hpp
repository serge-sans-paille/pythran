//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_CONTAINER_CONJ_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_CONTAINER_CONJ_HPP_INCLUDED

#include <nt2/arithmetic/functions/conj.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/transpose.hpp>

namespace nt2 { namespace ext
{
  // conj optimizations
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::conj_, tag::cpu_
                            , (A0)
                            , ((node_<A0, nt2::tag::transpose_, boost::mpl::long_<1>, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), ctranspose(boost::proto::child_c<0>(a0)))
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::conj_, tag::cpu_
                            , (A0)
                            , ((node_<A0, nt2::tag::ctranspose_, boost::mpl::long_<1>, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), transpose(boost::proto::child_c<0>(a0)))
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::conj_, tag::cpu_
                            , (A0)
                            , ((node_<A0, nt2::tag::conj_, boost::mpl::long_<1>, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), boost::proto::child_c<0>(a0))
  };
} }

#endif
