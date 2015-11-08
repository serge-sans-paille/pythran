//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_RAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_RAND_HPP_INCLUDED

#include <nt2/core/functions/rand.hpp>
#include <nt2/core/include/functions/as_size.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  /// size(...)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rand_, tag::cpu_
                            , (A0)
                            , ((ast_< A0, nt2::container::domain >))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0)
                          , nt2::rand(nt2::as_size(a0))
                          )
  };

  /// INTERNAL ONLY
  /// size(...) + target
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rand_, tag::cpu_
                            , (A0)(T)
                            , ((ast_< A0, nt2::container::domain >))
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, T const& tgt)
                          , (nt2::rand(nt2::as_size(a0),tgt))
                          )
  };

} }

#endif
