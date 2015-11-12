//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_PROLATE_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_PROLATE_HPP_INCLUDED
#include <nt2/gallery/functions/prolate.hpp>
#include <nt2/include/functions/sincpi.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/toeplitz.hpp>

namespace nt2
{
  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::prolate_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      typedef typename T::type t_t;
      BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const& t),(A0 const& n, T const& ),
                             (nt2::prolate(n, nt2::Quarter<t_t>()))
                            )
        };

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::prolate_, tag::cpu_,
                                (A0)(A1),
                                (scalar_<integer_<A0> >)
                                (scalar_<floating_<A1> >)

                              )
    {
       BOOST_DISPATCH_RETURNS(2, (A0 const& n, A1 const& w),
                              (nt2::toeplitz(Half<A1>()*nt2::sincpi(nt2::Two<A1>()*w*nt2::_(A1(0), A1(n-1)))))
                             )
         };

  }

  meta::call<tag::prolate_(const ptrdiff_t &, meta::as_<double> const &)>::type
  prolate(ptrdiff_t n)
  {
    return nt2::prolate(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::prolate_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  prolate(ptrdiff_t n)
  {
    return nt2::prolate(n,  meta::as_<T>());
  }

}


#endif
