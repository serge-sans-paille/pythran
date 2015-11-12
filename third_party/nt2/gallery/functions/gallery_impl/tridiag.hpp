//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_TRIDIAG_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_TRIDIAG_HPP_INCLUDED
#include <nt2/gallery/functions/tridiag.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/repnum.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tridiag_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> > )
    )
  {
    typedef typename nt2::meta::call<nt2::tag::tridiag_(const A0&, nt2::meta::as_<double> )>::type   result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& n) const
    {
      return tridiag(n, meta::as_<double>());
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tridiag_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> > )
                              (target_< scalar_<unspecified_<T> > > )
    )
  {
    typedef typename T::type  v_type;
    typedef typename nt2::meta::call<nt2::tag::tridiag_(const A0&, v_type, v_type, v_type)>::type   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& n,
                                             T const& ) const
    {
      return tridiag(n, v_type(-1), v_type(2), v_type(-1));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tridiag_, tag::cpu_,
                              (A0)(A1)(A2)(A3),
                              (scalar_<integer_<A0> > )
                              (scalar_<unspecified_<A1> >)
                              (scalar_<unspecified_<A2> >)
                              (scalar_<unspecified_<A3> >)
    )
  {
    typedef typename nt2::meta::call<nt2::tag::repnum_(const A1&, size_t, size_t)>::type  T0;
    typedef typename nt2::meta::call<nt2::tag::repnum_(const A2&, size_t, size_t)>::type  T1;
    typedef typename nt2::meta::call<nt2::tag::repnum_(const A3&, size_t, size_t)>::type  T2;
    typedef typename nt2::meta::call<nt2::tag::tridiag_(T0, T1, T2)>::type       result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& n,
                                             A1 const& lower,
                                             A2 const& diag,
                                             A3 const& super) const
    {
      size_t nm1 = nt2::minusone(n);
      return tridiag(nt2::repnum(lower, nm1, One<size_t>()),
                     nt2::repnum(diag, size_t(n), One<size_t>()),
                     nt2::repnum(super, nm1, One<size_t>())
        );
    }
  };

   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tridiag_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                              ((ast_<A2, nt2::container::domain>))
    )
  {
    typedef typename nt2::meta::call<nt2::tag::repnum_(const A0&, size_t, size_t)>::type          S0;
    typedef typename nt2::meta::call<nt2::tag::repnum_(const A1&, size_t, size_t)>::type          S1;
    typedef typename nt2::meta::call<nt2::tag::tridiag_(S0, S1, const A2&)>::type        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      return tridiag(nt2::repnum(a0, nt2::numel(a2), size_t(1)),
                     nt2::repnum(a1, oneplus(nt2::numel(a2)), size_t(1)),
                     a2);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tridiag_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<unspecified_<A1> >)
                              (scalar_<unspecified_<A2> >)
    )
  {
    typedef typename nt2::meta::call<nt2::tag::repnum_(const A1&, size_t, size_t)>::type          S1;
    typedef typename nt2::meta::call<nt2::tag::repnum_(const A2&, size_t, size_t)>::type          S2;
    typedef typename nt2::meta::call<nt2::tag::tridiag_(const A0&, S1, S2)>::type        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      return tridiag(a0,
                     nt2::repnum(a1, nt2::oneplus(nt2::numel(a0)), size_t(1)),
                     nt2::repnum(a2, nt2::numel(a0), size_t(1)));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tridiag_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<unspecified_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_<unspecified_<A2> >)
    )
  {
    typedef typename nt2::meta::call<nt2::tag::repnum_(const A0&, size_t, size_t)>::type          S0;
    typedef typename nt2::meta::call<nt2::tag::repnum_(const A2&, size_t, size_t)>::type          S2;
    typedef typename nt2::meta::call<nt2::tag::tridiag_(S0, const A1&, S2)>::type        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      size_t n =  nt2::minusone(nt2::numel(a1));
      return tridiag(nt2::repnum(a0, n, size_t(1)),
                     a1,
                     nt2::repnum(a2, n, size_t(1))
        );
    }
  };

   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tridiag_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<unspecified_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
                              ((ast_<A2, nt2::container::domain>))
    )
  {
    typedef typename nt2::meta::call<nt2::tag::repnum_(const A0&, size_t, size_t)>::type                  S0;
    typedef typename nt2::meta::call<nt2::tag::tridiag_(S0, const A1&, const A2&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      return tridiag(nt2::repnum(a0, nt2::numel(a2), size_t(1)),
                     a1,
                     a2);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tridiag_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<unspecified_<A1> >)
                              ((ast_<A2, nt2::container::domain>))
    )
  {
    typedef typename nt2::meta::call<nt2::tag::repnum_(const A1&, size_t, size_t)>::type                  S1;
    typedef typename nt2::meta::call<nt2::tag::tridiag_(const A0&, S1, const A2&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      return tridiag(a0,
                     nt2::repnum(a1, nt2::oneplus(nt2::numel(a2)), size_t(1)),
                     a2);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tridiag_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_<unspecified_<A2> >)
    )
  {
    typedef typename nt2::meta::call<nt2::tag::repnum_(const A2&, size_t, size_t)>::type                  S2;
    typedef typename nt2::meta::call<nt2::tag::tridiag_(const A0&, const A1&, S2)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      return tridiag(a0,
                     a1,
                     nt2::repnum(a2, nt2::numel(a0), size_t(1))
        );
    }
  };


 NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tridiag_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              ((ast_<A2, nt2::container::domain>))
    )
  {

    BOOST_DISPATCH_RETURNS(3, (A0 const& lower, A1 const& diag, A2 const& super),
                           (nt2::from_diag(nt2::colvect(super),ptrdiff_t(1))+
                            nt2::from_diag(nt2::colvect(diag)) +
                            nt2::from_diag(nt2::colvect(lower),ptrdiff_t(-1))
                           )
                          )
      };
} }


#endif

