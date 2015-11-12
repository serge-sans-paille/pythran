//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_SAMPLING_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_SAMPLING_HPP_INCLUDED
#include <nt2/gallery/functions/sampling.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/is_invalid.hpp>


namespace nt2
{

  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sampling_, tag::cpu_,
                                (A0),
                                ((ast_<A0, nt2::container::domain>))
                              )
    {
      typedef typename meta::call<tag::colvect_(A0 const&)>::type            T0;
      typedef typename meta::call<tag::expand_to_(T0, size_t, size_t)>::type T1;
      typedef typename meta::call<tag::transpose_(T1)>::type                 T2;
      typedef typename meta::call<tag::divides_(T2, T1)>::type               T3;
      typedef typename meta::call<tag::oneminus_(T3)>::type                  T4;
      typedef typename meta::call<tag::rec_(T4)>::type                       T5;
      typedef typename meta::call<tag::is_invalid_(T5)>::type                T6;
      typedef typename meta::call<tag::if_zero_else_(T6,T5)>::type           T8;
      typedef typename meta::call<tag::sum_(T8)>::type                       T9;
      typedef typename meta::call<tag::from_diag_(T9)>::type                T10;
      typedef typename meta::call<tag::plus_(T8, T10)>::type        result_type;
    NT2_FUNCTOR_CALL(1)
    {

       BOOST_AUTO_TPL(x, nt2::colvect(a0));
       size_t n = numel(a0);
       BOOST_AUTO_TPL(y, nt2::expand_to(x, n, n));
       BOOST_AUTO_TPL(z, nt2::rec(nt2::oneminus(nt2::transpose(y)/y)));
       BOOST_AUTO_TPL(a, if_zero_else(is_invalid(z), z));
       return a + nt2::from_diag(nt2::sum(a));
    }
  };



    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sampling_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      typedef typename T::type t_t;
      BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const& t), (A0 const& n, T const& ),
                             (nt2::sampling(nt2::_(t_t(1), t_t(n))))
                            )
        };

  }

  meta::call<tag::sampling_(const ptrdiff_t &, meta::as_<double> const &)>::type
  sampling(ptrdiff_t n)
  {
    return nt2::sampling(nt2::_(1.0, double(n)));
  }
  template<class T>
  typename meta::call<tag::sampling_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  sampling(ptrdiff_t n)
  {
    return nt2::sampling(nt2::_(T(1), T(n)));
  }

}


#endif
