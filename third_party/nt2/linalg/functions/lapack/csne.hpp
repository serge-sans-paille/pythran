//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_CSNE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_CSNE_HPP_INCLUDED

#include <nt2/linalg/functions/csne.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::csne_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type ctype_t;
    typedef typename nt2::container::table<ctype_t> t_t;
    typedef nt2::memory::container<tag::table_, ctype_t, nt2::settings(nt2::_2D)> desired_semantic;
    typedef  t_t                                      result_type;

     BOOST_FORCEINLINE result_type operator()(A0 const& A, A1 const& B) const
    {
      NT2_AS_TERMINAL_IN(desired_semantic,a,A);
      NT2_AS_TERMINAL_IN(desired_semantic,b,B);

      nt2_la_int na = nt2::width(a);

      t_t x;
      nt2::container::table<ctype_t,nt2::upper_triangular_> e,r;
      r = nt2::qr(a);
      r= nt2::triu( r( _(1,na), _ ) );

      x= nt2::mtimes(nt2::trans(a),b);

      x = nt2::linsolve(nt2::trans(r),x);
      x = nt2::linsolve(r,x);

      // One-step refinement
      e = b - nt2::mtimes(a,x);
      e = nt2::mtimes(nt2::trans(a),e);

      e = nt2::linsolve(nt2::trans(r),e);
      e = nt2::linsolve(r,e);

      return x + e;
    }
  };

} }

#endif
