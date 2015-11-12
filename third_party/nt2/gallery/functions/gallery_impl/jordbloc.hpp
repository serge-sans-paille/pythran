//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_JORDBLOC_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_JORDBLOC_HPP_INCLUDED
#include <nt2/gallery/functions/jordbloc.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/ones.hpp>

namespace nt2 {namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::jordbloc_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<floating_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& n, A1 const& lambda),
                           (lambda*nt2::eye(n, meta::as_<A1>())+ nt2::from_diag(ones(n-1,1, meta::as_<A1>()),1))
                          )
  };

} }

#endif
