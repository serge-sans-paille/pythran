//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_CROSS_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_CROSS_HPP_INCLUDED

#include <nt2/include/functions/cross.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/functions/cat.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/functions/arecrosscompatible.hpp>
#include <nt2/include/functions/firstoflength.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/core/container/dsl.hpp>
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cross_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {

    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
                           (nt2::cross(a0, a1, nt2::firstoflength(a0, 3))
                           )
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cross_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename  meta::call<tag::along_(const A0&, size_t, const A2&)>::type X;
    typedef typename  meta::call<tag::along_(const A1&, size_t, const A2&)>::type Y;
    typedef typename  meta::call<tag::multiplies_(X, Y)>::type                   XY;
    typedef typename  meta::call<tag::minus_(XY, XY)>::type                   XYmXY;
    typedef typename  meta::call<tag::cat_(const A2&, XYmXY, XYmXY)>::type        C;
    typedef typename  meta::call<tag::cat_(const A2&, C, XYmXY)>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& x, A1 const & y, A2 const & dim) const
    {
      BOOST_ASSERT_MSG(nt2::arecrosscompatible(x, y, dim), "in cross: x and y must have the same dimensions and dimension dim must have 3 elements");
      BOOST_AUTO_TPL(x1, nt2::along(x, size_t(1), dim));
      BOOST_AUTO_TPL(x2, nt2::along(x, size_t(2), dim));
      BOOST_AUTO_TPL(x3, nt2::along(x, size_t(3), dim));
      BOOST_AUTO_TPL(y1, nt2::along(y, size_t(1), dim));
      BOOST_AUTO_TPL(y2, nt2::along(y, size_t(2), dim));
      BOOST_AUTO_TPL(y3, nt2::along(y, size_t(3), dim));
      return nt2::cat(dim,
                      nt2::cat(dim,
                               (x2*y3 - x3*y2),
                               (x3*y1 - x1*y3)),
                      (x1*y2 - x2*y1));

    }
  };
} }

#endif
