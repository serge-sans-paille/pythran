//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_BLKDIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_BLKDIAG_HPP_INCLUDED

#include <nt2/core/functions/blkdiag.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/horzcat.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::blkdiag_, tag::cpu_, (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0  result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a) const
    {
      return a;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::blkdiag_, tag::cpu_, (A0)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A0 const& a1),
                           nt2::diag_of(nt2::horzcat(a0, a1))
                           )
  };


} }

#endif
