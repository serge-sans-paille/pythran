//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_LEHMER_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_LEHMER_HPP_INCLUDED
#include <nt2/gallery/functions/lehmer.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/whereij.hpp>
#include <nt2/include/functor.hpp>

namespace nt2 {namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lehmer_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const& t),(A0 const& n, T const& ),
                           (nt2::whereij(nt2::functor<nt2::tag::is_less_equal_>(),
                                    nt2::rif(n, T())/nt2::cif(n, T()),
                                    nt2::cif(n, T())/nt2::rif(n, T())
                                        )
                           )
                          )
      };

} }

#endif
