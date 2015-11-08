//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_EXPR_COMPAN_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_EXPR_COMPAN_HPP_INCLUDED
#include <nt2/polynom/functions/compan.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/reduce.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/reduce.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::compan_, tag::cpu_
                              , (A0)
                              , ((ast_<A0, nt2::container::domain>))
                            )
  {

    typedef typename A0::value_type value_type;
    typedef typename nt2::meta::call<nt2::tag::rowvect_(const A0&)>::type                           S;
    typedef typename nt2::meta::call<nt2::tag::reduce_(S)>::type                                   T0;
    typedef meta::as_<value_type>                                                                  T1;
    typedef typename nt2::meta::call<nt2::tag::One(size_t, size_t, T1)>::type                      T2;
    typedef typename nt2::meta::call<nt2::tag::from_diag_(T2, ptrdiff_t)>::type                    T3;
    typedef typename nt2::meta::call<nt2::tag::colon_(size_t, size_t)>::type                       T4;
    typedef typename nt2::meta::call<nt2::tag::function_(T0, T4)>::type                            T5;
    typedef typename nt2::meta::call<nt2::tag::divides_(T5, value_type)>::type                     T6;
    typedef typename nt2::meta::call<nt2::tag::function_(T3, T4, nt2::container::colon_)>::type    T7;
    typedef typename nt2::meta::call<nt2::tag::vertcat_(T6, T7)>::type                    result_type;
    NT2_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG(isvector(a0), "Input argument must be a vector.");
      BOOST_AUTO_TPL(p,  nt2::reduce(nt2::rowvect(a0)));
      size_t np = nt2::numel(p);
      value_type f = nt2::One<value_type>();
      if (np) f = -p(1);
      ptrdiff_t nd = np-2 ? -1 :0;
      BOOST_AUTO_TPL(d, nt2::from_diag(nt2::ones(nt2::of_size(1, np-2), meta::as_<value_type>()), nd));
      BOOST_AUTO_TPL(g, p(nt2::_(nt2::Two<size_t>(), np ))/f);
      BOOST_AUTO_TPL(h, d(nt2::_(nt2::Two<size_t>(), size_t(np-1)), nt2::_));
      return nt2::catv(g, h);
    }
  };
} }


#endif
